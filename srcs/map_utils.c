/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:49:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/04 16:28:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_utils.h"
#include <float.h>
#include <stdlib.h>
#define F_NEAR (0.0001)

t_point	add_map_point(t_point point, int x, int y)
{
	point.x += x;
	point.y += y;
	return (point);
}

t_point	get_point(int x, int y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}

t_point get_player_map_point(t_cub3d *cub3d)
{
	t_point point;

	point.x = cub3d->player->map.x;
	point.y = cub3d->player->map.y;
	return (point);
}

t_point next_map_mass(t_cub3d_type angle, t_cub3d_type x_dist, t_cub3d_type y_dist, t_point map)
{

	if (fabs(angle - 0) <= D_EQUAL)
		return (add_map_point(map, 0, -1));
	else if (fabs(angle - (M_PI / 2)) <= D_EQUAL)
		return (add_map_point(map, -1, 0));
	else if (fabs(angle - (M_PI)) <= D_EQUAL)
		return (add_map_point(map, 0, 1));
	else if (fabs(angle - (M_PI * 3 / 2)) <= D_EQUAL)
		return (add_map_point(map, 1, 0));
	if (angle <= M_PI / 2)
	{
		if ((x_dist >= y_dist * fabs(tan(angle)) || fabs(x_dist - y_dist * tan(angle)) < F_NEAR) && tan(angle) != NAN)
			return (add_map_point(map, 0, -1));
		else
			return (add_map_point(map, -1, 0));
	}
	else if (angle <= M_PI)
	{
		if (x_dist <= y_dist * fabs(tan(angle)) || fabs(x_dist - y_dist * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, -1, 0));
		else
			return (add_map_point(map, 0, 1));
	}
	else if (angle <= M_PI * 3 / 2)
	{
		if (x_dist >= y_dist * fabs(tan(angle)) || fabs(x_dist - y_dist * fabs(tan(angle))) <= F_NEAR)
			return (add_map_point(map, 0, 1));
		else
			return (add_map_point(map, 1, 0));
	}
	if (x_dist <= y_dist * fabs(tan(angle)) || fabs(x_dist - y_dist * fabs(tan(angle))) <= F_NEAR)
		return (add_map_point(map, 1, 0));
	return (add_map_point(map, 0, -1));
}

t_cub3d_type	convert_positive_radian(t_cub3d_type radian)
{
	if (radian < 0)
		return (radian + 2 * M_PI);
	return (radian);
}

t_point	get_wall_distance_from_player(t_cub3d *cub3d, t_point map_point, t_point offset)
{
	t_point distance;

	distance.x = ((int)((cub3d->player->map.x - (map_point.x + offset.x))) * WALL_LEN + cub3d->player->mass.x);
	distance.y = ((int)((cub3d->player->map.y - (map_point.y + offset.y))) * WALL_LEN + cub3d->player->mass.y);
	return (distance);
}

t_wall_dir	get_wall_direction(t_point old, t_point cur)
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

int	is_collision_wall(t_cub3d *cub3d, t_ray * ray, t_cub3d_type angle, t_point src_map)
{
	t_cub3d_type    y_dist;
	t_cub3d_type    x_dist;
	t_point         next;

	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		y_dist = cub3d->player->world_y - src_map.y * WALL_LEN;
	else
		y_dist = (src_map.y + 1) * WALL_LEN - cub3d->player->world_y;
	if (angle < M_PI && angle > 0)
		x_dist = cub3d->player->world_x - src_map.x * WALL_LEN;
	else
		x_dist = (src_map.x + 1) * WALL_LEN - cub3d->player->world_x;
	next = next_map_mass(angle, x_dist, y_dist, src_map);
	//printf("angle=%lf, next:x=%d, y=%d, x_dist=%lf, y_dist=%lf\n",angle * 180 / M_PI, next.x, next.y, x_dist, y_dist);
	if (ray->map_point.x == next.x && ray->map_point.y == next.y)
	{
		if (get_wall_direction(src_map, next) == ray->wall_dir)
			return (true);
		return (false);
	}
	else if (cub3d->map[next.y][next.x].obj == WALL || cub3d->map[next.y][next.x].obj >= DOOR)
		return (false);
	return (is_collision_wall(cub3d, ray, angle, next));
}
