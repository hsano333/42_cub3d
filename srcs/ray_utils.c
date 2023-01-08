/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:59:08 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 16:34:20 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_utils.h"
#include "map_utils.h"
#define F_NEAR (0.0001)

static t_point	which_mass(double angle, t_distance dist, t_point map, double y)
{
	if (angle <= M_PI / 2)
	{
		if ((dist.x >= y || fabs(dist.x - dist.y * tan(angle)) < F_NEAR))
			return (add_map_point(map, 0, -1));
		else
			return (add_map_point(map, -1, 0));
	}
	else if (angle <= M_PI)
	{
		if (dist.x <= y || fabs(dist.x - dist.y * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, -1, 0));
		else
			return (add_map_point(map, 0, 1));
	}
	else if (angle <= M_PI * 3 / 2)
	{
		if (dist.x >= y || fabs(dist.x - dist.y * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, 0, 1));
		else
			return (add_map_point(map, 1, 0));
	}
	if (dist.x <= y || fabs(dist.x - dist.y * fabs(tan(angle))) <= F_NEAR)
		return (add_map_point(map, 1, 0));
	return (add_map_point(map, 0, -1));
}

static t_point	next_map_mass(double angle, double x_dist \
									, double y_dist, t_point map)
{
	t_distance	dist;
	double		tmp_y_dist;

	tmp_y_dist = y_dist * fabs(tan(angle));
	dist.x = x_dist;
	dist.y = y_dist;
	if (fabs(angle - 0) <= D_EQUAL)
		return (add_map_point(map, 0, -1));
	else if (fabs(angle - (M_PI / 2)) <= D_EQUAL)
		return (add_map_point(map, -1, 0));
	else if (fabs(angle - (M_PI)) <= D_EQUAL)
		return (add_map_point(map, 0, 1));
	else if (fabs(angle - (M_PI * 3 / 2)) <= D_EQUAL)
		return (add_map_point(map, 1, 0));
	return (which_mass(angle, dist, map, tmp_y_dist));
}

static t_wall_dir	get_wall_direction(t_point old, t_point cur)
{
	int	diff_x;
	int	diff_y;

	diff_x = cur.x - old.x;
	diff_y = cur.y - old.y;
	if (diff_y == -1)
		return (SOUTH_WALL);
	else if (diff_y == 1)
		return (NORTH_WALL);
	else if (diff_x == 1)
		return (WEST_WALL);
	return (EAST_WALL);
	return (false);
}

t_point	search_wall(t_cub3d *cub3d \
			, t_ray *ray, double angle, t_point map)
{
	double		y_dist;
	double		x_dist;
	t_point		next;

	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		y_dist = cub3d->player->world_y - map.y * WALL_LEN;
	else
		y_dist = (map.y + 1) * WALL_LEN - cub3d->player->world_y;
	if (angle < M_PI && angle > 0)
		x_dist = cub3d->player->world_x - map.x * WALL_LEN;
	else
		x_dist = (map.x + 1) * WALL_LEN - cub3d->player->world_x;
	next = next_map_mass(angle, x_dist, y_dist, map);
	if (cub3d->map[next.y][next.x].obj == WALL \
					|| (cub3d->map[next.y][next.x].obj >= DOOR && cub3d->map[next.y][next.x].state == CLOSE))
	{
		set_map_dir(cub3d, ray, map, next);
		if (cub3d->map[next.y][next.x].obj >= DOOR)
		{
			ray->wall_img = cub3d->walls->sprite;
			ray->is_door = true;
		}
		return (next);
	}
	return (search_wall(cub3d, ray, angle, next));
}

int	is_collision_wall(t_cub3d *cub3d, t_ray *ray \
						, double angle, t_point src_map)
{
	double			y_dist;
	double			x_dist;
	t_point			next;

	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		y_dist = cub3d->player->world_y - src_map.y * WALL_LEN;
	else
		y_dist = (src_map.y + 1) * WALL_LEN - cub3d->player->world_y;
	if (angle < M_PI && angle > 0)
		x_dist = cub3d->player->world_x - src_map.x * WALL_LEN;
	else
		x_dist = (src_map.x + 1) * WALL_LEN - cub3d->player->world_x;
	next = next_map_mass(angle, x_dist, y_dist, src_map);
	if (ray->map_point.x == next.x && ray->map_point.y == next.y)
	{
		if (get_wall_direction(src_map, next) == ray->wall_dir)
			return (true);
		return (false);
	}
	else if (cub3d->map[next.y][next.x].obj == WALL \
						|| cub3d->map[next.y][next.x].obj >= DOOR)
		return (false);
	return (is_collision_wall(cub3d, ray, angle, next));
}
