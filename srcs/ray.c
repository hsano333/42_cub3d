/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2023/01/02 18:56:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "angle_utils.h"
#include "map_utils.h"
#include <float.h>

static void	set_map_dir(t_cub3d *cub3d, t_ray *ray, t_point map, t_point next_map)
{
	int	diff_x;
	int	diff_y;

	diff_x = next_map.x - map.x;
	diff_y = next_map.y - map.y;

	if (diff_y == -1)
	{
		//printf("south\n");
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->north;
	}
	else if (diff_y == 1)
	{
		//printf("north\n");
		ray->wall_dir = NORTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (diff_x == 1)
	{
		//printf("west\n");
		ray->wall_dir = WEST_WALL;
		ray->wall_img = cub3d->walls->east;
	}
	else if (diff_x == -1)
	{
		//printf("east\n");
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->west;
	}
}

static	t_point search_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle, t_point map)
{
	t_cub3d_type	y_dist;
	t_cub3d_type	x_dist;
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
	if (cub3d->map[next.y][next.x].obj == WALL || cub3d->map[next.y][next.x].obj >= DOOR)
	{
		set_map_dir(cub3d, ray, map, next);
		return (next);
	}
	return (search_wall(cub3d, ray, angle, next));
}

#define FIRST 0
#define LAST 1

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

int	is_next_wall(t_ray *ray, t_cub3d_type angle)
{
	if (ray->begin_angle >= ray->last_angle && angle <= ray->last_angle)
		return (true);
	else if (ray->begin_angle < ray->last_angle)
	{
		if (angle > ray->begin_angle && angle <= ray->last_angle)
			return (true);
	}
	return (false);
}

static t_point	get_distance_from_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	t_point	begin_distance;
	t_point	last_distance;
	t_point	offset;

	offset = get_offset(ray, FIRST);
	begin_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	begin_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	ray->begin_distance = begin_distance;
	offset = get_offset(ray, LAST);
	last_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	last_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	ray->last_distance = last_distance;
	ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, angle, RORATE_PLUS);
	ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle, RORATE_MINUS);
	ray->base_angle = angle;

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
	ray->begin_x = ray->x;
	double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) / WALL_LEN;
	double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) / WALL_LEN;
	if (begin_distance.x == last_distance.x)
	{
		ray->img_offset_begin = ((begin_distance.x / tan(angle) - begin_distance.x / tan(ray->begin_angle)) * base_x);
		ray->img_offset_last = cub3d->player->y;
		ray->base_distance.x = begin_distance.x;
		ray->base_distance.y = begin_distance.x / tan(angle);
	}
	else
	{
		ray->img_offset_begin = ((begin_distance.y * tan(angle) - begin_distance.y * tan(ray->begin_angle)) * base_y);
		ray->img_offset_last = cub3d->player->x;
		ray->base_distance.x = begin_distance.y / tan(angle);
		ray->base_distance.y = begin_distance.y;
	}
	if (ray->x != 0)
		ray->img_offset_begin = 0;
	if (ray->last_angle < 0)
		ray->last_angle += (double)(360 * M_PI / 180);
	return (begin_distance);
}

int	fire_ray(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	ray->x = 1;
	ray->map_point = search_wall(cub3d, ray, angle, get_player_map_point(cub3d));
	ray->distance = get_distance_from_wall(cub3d, ray, angle);
	return (true);
}
