/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 13:17:04 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "map_utils.h"
#include "ray.h"
#include "angle_utils.h"
#include "map_utils.h"
#define FIRST 0
#define LAST 1

static void	set_map_dir(t_cub3d *cub3d, t_ray *ray, t_point map, t_point next_map)
{
	int	diff_x;
	int	diff_y;

	diff_x = next_map.x - map.x;
	diff_y = next_map.y - map.y;

	if (diff_y == -1)
	{
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->north;
	}
	else if (diff_y == 1)
	{
		ray->wall_dir = NORTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (diff_x == 1)
	{
		ray->wall_dir = WEST_WALL;
		ray->wall_img = cub3d->walls->east;
	}
	else if (diff_x == -1)
	{
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->west;
	}
}

static t_point	get_offset(t_ray *ray, int mode)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	if (mode == FIRST)
	{
		if (ray->wall_dir == NORTH_WALL)
			point.x = 1;
		else if (ray->wall_dir == SOUTH_WALL)
			point.y = 1;
		else if (ray->wall_dir == EAST_WALL)
		{
			point.x = 1;
			point.y = 1;
		}
	}
	else if (ray->wall_dir == SOUTH_WALL)
	{
		point.x = 1;
		point.y = 1;
	}
	else if (ray->wall_dir == EAST_WALL)
		point.x = 1;
	else if (ray->wall_dir == WEST_WALL)
		point.y = 1;
	return (point);
}


static	t_point search_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle, t_point map)
{

	t_cub3d_type    y_dist;
	t_cub3d_type    x_dist;
	t_point         next;

	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		y_dist = cub3d->player->world_y - map.y * WALL_LEN;
	else
		y_dist = (map.y + 1) * WALL_LEN - cub3d->player->world_y;
	if (angle < M_PI && angle > 0)
		x_dist = cub3d->player->world_x - map.x * WALL_LEN;
	else
		x_dist = (map.x + 1) * WALL_LEN - cub3d->player->world_x;
	next = next_map_mass(angle, x_dist, y_dist, map);
	if (cub3d->map[next.y][next.x].obj == WALL || cub3d->map[next.y][next.x].obj >= DOOR)
	{
		set_map_dir(cub3d, ray, map, next);
		return (next);
	}
	return (search_wall(cub3d, ray, angle, next));
}

t_cub3d_type	get_stop_angle(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	const t_cub3d_type	sub_angle = (t_cub3d_type)1 * M_PI / 180;
	int	i;
	int	over_flag;
//
	over_flag = false;
	if (!is_in_range_fov(cub3d, angle))
		angle = cub3d->angles[WIN_WIDTH - 1].radian + cub3d->player->dir.radian;
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (ray->start_angle < ray->last_angle)
		over_flag = true;
	i = 0;
	while (!is_collision_wall(cub3d, ray, angle, cub3d->player->map))
	{
		i++;
		angle += sub_angle;
		if (angle > 2 * M_PI)
			angle -= 2 * M_PI;
		if (!over_flag && angle > ray->start_angle)
		{
			angle = ray->start_angle - sub_angle / 10;
			if (angle < 0)
				angle += 2 * M_PI;
			return (angle);
		}
	}
	return (angle);
}

int	is_next_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	if (ray->start_angle >= ray->stop_angle && angle <= ray->stop_angle)
	{
		if (is_collision_wall(cub3d, ray, angle, cub3d->player->map))
			return (false);
		else
			return (true);
	}
	else if (ray->start_angle < ray->stop_angle)
	{
		if (angle > ray->start_angle && angle <= ray->stop_angle)
		{
			if (is_collision_wall(cub3d, ray, angle, cub3d->player->map))
				return (false);
			else
				return (true);
		}

	}
	return (false);
}

/*
int	is_front_wall()
{
	ray->is_front_wall = false;
	if (cub3d->player->dir.radian >= M_PI * 7 / 4 || cub3d->player->dir.radian < M_PI / 4)
	{
		if (ray->wall_dir == NORTH_WALL || ray->wall_dir == SOUTH_WALL)
			ray->is_front_wall = true;
	}
	else if (cub3d->player->dir.radian >= M_PI  / 4 && cub3d->player->dir.radian < M_PI * 3 / 4)
	{
		if (ray->wall_dir == EAST_WALL || ray->wall_dir == WEST_WALL)
			ray->is_front_wall = true;
	}
	else if (cub3d->player->dir.radian >= M_PI * 3 / 4 && cub3d->player->dir.radian < M_PI * 5 / 4)
	{
		if (ray->wall_dir == NORTH_WALL || ray->wall_dir == SOUTH_WALL)
			ray->is_front_wall = true;

	}
	else
	{
		if (ray->wall_dir == EAST_WALL || ray->wall_dir == WEST_WALL)
			ray->is_front_wall = true;
	}
}
*/

static void	calc_ray_to_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	t_point	offset;

	offset = get_offset(ray, FIRST);
	ray->begin_distance = get_wall_distance_from_player(cub3d, ray->map_point, offset);
	offset = get_offset(ray, LAST);
	ray->last_distance = get_wall_distance_from_player(cub3d, ray->map_point, offset);
	ray->begin_angle = distance_to_angle((double)ray->begin_distance.x / ray->begin_distance.y, angle, RORATE_PLUS);
	ray->last_angle = distance_to_angle((double)ray->last_distance.x / ray->last_distance.y, angle, RORATE_MINUS);
	ray->start_angle = angle;
	ray->stop_angle = get_stop_angle(cub3d, ray, ray->last_angle);
	ray->begin_base_len = tan(ray->begin_angle - cub3d->player->dir.radian);
	ray->last_base_len = tan(ray->last_angle - cub3d->player->dir.radian);
	ray->max_len =  ray->last_base_len - ray->begin_base_len;
}

int	fire_ray(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	ray->map_point = search_wall(cub3d, ray, angle, get_player_map_point(cub3d));
	calc_ray_to_wall(cub3d, ray, angle);
	ray->is_adjacent_wall = false;
	//printf("fire_ray No.1 map:x=%d, y=%d, mass:x=%d, y=%d, wall_point:x=%d, y=%d\n", cub3d->player->map.x, cub3d->player->map.y, cub3d->player->mass.x, cub3d->player->mass.y, ray->map_point.x, ray->map_point.y);
	if (((fabs(ray->map_point.x - cub3d->player->map.x) == 1) && (fabs(ray->map_point.y - cub3d->player->map.y) == 0)) || ((fabs(ray->map_point.x - cub3d->player->map.x) == 0) && (fabs(ray->map_point.y - cub3d->player->map.y) == 1)))
		ray->is_adjacent_wall = true;
	//printf("fire_ray No.2 is_flag = %d, %d, map:x=%d, y=%d, mass:x=%d, y=%d, wall_point:x=%d, y=%d\n",ray->is_adjacent_wall, ray->is_adjacent_wall, cub3d->player->map.x, cub3d->player->map.y, cub3d->player->mass.x, cub3d->player->mass.y, ray->map_point.x, ray->map_point.y);
	return (true);
}
