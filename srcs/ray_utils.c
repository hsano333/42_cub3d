/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 00:59:08 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 03:10:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_utils.h"
#include "map_utils.h"
#define F_NEAR (0.0001)

static void	set_map_dir(t_cub3d *cub3d, t_ray *ray \
						, t_point map, t_point next_map)
{
	t_point	diff;

	diff.x = next_map.x - map.x;
	diff.y = next_map.y - map.y;
	if (diff.y == -1)
	{
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->north;
	}
	else if (diff.y == 1)
	{
		ray->wall_dir = NORTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (diff.x == 1)
	{
		ray->wall_dir = WEST_WALL;
		ray->wall_img = cub3d->walls->east;
	}
	else if (diff.x == -1)
	{
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->west;
	}
}

static t_point	which_mass(double angle, double x, double y, t_point map)
{
	double	y_dist;

	y_dist = y * fabs(tan(angle));
	if (angle <= M_PI / 2)
	{
		if ((x >= y_dist || fabs(x - y * tan(angle)) < F_NEAR))
			return (add_map_point(map, 0, -1));
		else
			return (add_map_point(map, -1, 0));
	}
	else if (angle <= M_PI)
	{
		if (x <= y_dist || fabs(x - y * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, -1, 0));
		else
			return (add_map_point(map, 0, 1));
	}
	else if (angle <= M_PI * 3 / 2)
	{
		if (x >= y_dist || fabs(x - y * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, 0, 1));
		else
			return (add_map_point(map, 1, 0));
	}
	return (add_map_point(map, 1, 0));
}

static t_point	next_map_mass(double angle, double x_dist \
									, double y_dist, t_point map)
{
	if (fabs(angle - 0) <= D_EQUAL)
		return (add_map_point(map, 0, -1));
	else if (fabs(angle - (M_PI / 2)) <= D_EQUAL)
		return (add_map_point(map, -1, 0));
	else if (fabs(angle - (M_PI)) <= D_EQUAL)
		return (add_map_point(map, 0, 1));
	else if (fabs(angle - (M_PI * 3 / 2)) <= D_EQUAL)
		return (add_map_point(map, 1, 0));
	return (which_mass(angle, x_dist, y_dist, map));
}

t_point	search_wall(t_cub3d *cub3d \
			, t_ray *ray, double angle, t_point map)
{
	double			y_dist;
	double			x_dist;
	t_point			next;

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
					|| cub3d->map[next.y][next.x].obj >= DOOR)
	{
		set_map_dir(cub3d, ray, map, next);
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
