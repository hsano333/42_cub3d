/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2023/01/03 18:20:41 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
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
	//t_cub3d_type	y_dist;
	//t_cub3d_type	x_dist;
	t_point		next;



	//int x_diff;
	//int y_diff;

	//if (cos(angle) >= 0)
	//double cos = x * cos(angle);
	//double sin = y * sin(angle);

	//if (fabs(cos - x) - fabs(sin - y) > 0)

	next = next_map_mass(angle, cub3d->player->mass, cub3d->player->map);
	//printf("search_wall No.1 angle=%lf,next:x=%d, y=%d, cur:x=%d, y=%d\n",angle * 180 / M_PI, next.x, next.y, cub3d->player->map.x, cub3d->player->map.y);
	if (cub3d->map[next.y][next.x].obj == WALL || cub3d->map[next.y][next.x].obj >= DOOR)
	{
		//printf("set_map, search No.2 end \n");
		set_map_dir(cub3d, ray, map, next);
		return (next);
	}
	return (search_wall(cub3d, ray, angle, next));
}

//static t_cub3d_point	get_stop_angle(t_cub3d *cub3d, t_ray *ray, t_point wall_point, t_cub3d_type angle)
t_cub3d_type	get_stop_angle(t_cub3d *cub3d, t_cub3d_type angle, t_point wall_point)
{
	t_point		point;
	//t_cub3d_type	angle;
	//t_cub3d_type	tmp_last_angle;
	t_cub3d_type	tmp_start_angle;
	t_point		offset;
	t_point		last_distance;
	t_ray		ray;

	point.x = 0;
	point.y = 0;

	//angle = ray.last_angle;
	tmp_start_angle = angle;
		//printf("get_stop_angle No.0\n");
	while (1)
	{
		//printf("get_stop_angle No.1\n");
		point = search_wall(cub3d, &ray, angle, get_player_map_point(cub3d));
		if (point.x == wall_point.x && point.y == wall_point.y)
			return (tmp_start_angle);
		//printf("infinite?angle=%lf,  point.x=%d, point.y=%d,wall.x=%d, wall.y=%d\n",angle,point.x, point.y, wall_point.x, wall_point.y);
		//printf("infinite?\n");
		//point = search_wall(cub3d, ray, angle, get_player_map_point(cub3d));
		//if (point.x == ray->map_point.x && point.y == ray->map_point.y)
			//break ;
		offset = get_offset(&ray, FIRST);
		last_distance = get_wall_distance_from_player(cub3d, point, offset);
		tmp_start_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle, RORATE_PLUS);
		angle = tmp_start_angle + 1 *M_PI / 180;
		if (angle >= 2 * M_PI)
			angle += 2 * M_PI;
	}
	return (tmp_start_angle);
}

int	is_next_wall(t_ray *ray, t_cub3d_type angle)
{
	if (ray->begin_angle >= ray->last_angle && angle <= ray->stop_angle)
		return (true);
	else if (ray->begin_angle < ray->last_angle)
	{
		if (angle > ray->start_angle && angle <= ray->stop_angle)
			return (true);
	}
	/*
	if (ray->begin_angle >= ray->last_angle && angle <= ray->last_angle)
		return (true);
	else if (ray->begin_angle < ray->last_angle)
	{
		if (angle > ray->begin_angle && angle <= ray->last_angle)
			return (true);
	}
	*/
	return (false);
}

static t_point	get_distance_from_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	t_point	begin_distance;
	t_point	last_distance;
	t_point	offset;

	offset = get_offset(ray, FIRST);
	begin_distance = get_wall_distance_from_player(cub3d, ray->map_point, offset);
	ray->begin_distance = begin_distance;
	offset = get_offset(ray, LAST);
	last_distance = get_wall_distance_from_player(cub3d, ray->map_point, offset);
	ray->last_distance = last_distance;
	ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, angle, RORATE_PLUS);
	ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle, RORATE_MINUS);
	ray->start_angle = angle;
	ray->stop_angle = ray->last_angle;
	//ray->stop_angle = get_stop_angle(cub3d, ray->last_angle, ray->map_point);
	//printf("start_angle=%lf, stop_angle=%lf\n", ray->start_angle, ray->stop_angle);

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
		ray->img_offset_last = cub3d->player->mass.y;
		ray->base_distance.x = begin_distance.x;
		ray->base_distance.y = begin_distance.x / tan(angle);
	}
	else
	{
		ray->img_offset_begin = ((begin_distance.y * tan(angle) - begin_distance.y * tan(ray->begin_angle)) * base_y);
		ray->img_offset_last = cub3d->player->mass.x;
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
	//printf("fire_ray No.1 angle=%lf\n", angle * 180 / M_PI);
	ray->map_point = search_wall(cub3d, ray, angle, get_player_map_point(cub3d));
	ray->distance = get_distance_from_wall(cub3d, ray, angle);
	printf("fire map_point.x=%d, y=%d, distance.x=%d, y=%d\n", ray->map_point.x, ray->map_point.y, ray->distance.x, ray->distance.y);
	return (true);
}
