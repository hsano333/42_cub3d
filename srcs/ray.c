/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2022/12/20 14:16:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static	t_point search_wall(t_ray *ray)
{
	t_point	point;
	point.x = ray->x;
	point.y = 1;
	return (point);
}

#define FIRST 0
#define LAST 1

/*
static	adjust_distance(t_cub3d *cub3d, t_ray *ray, int mode)
{
	if (mode == FIRST)
	{
		if (ray->wall_dir == NORTH_WALL)
			distance.x -= WALL_LEN;
		else if (ray->wall_dir == SOUTH_WALL)
			distance.y -= WALL_LEN;
		else if (ray->wall_dir == WEST_WALL)
			;
		else if (ray->wall_dir == EAST_WALL)
		{
			distance.x -= WALL_LEN;
			distance.y -= WALL_LEN;
		}
	}
	else if(mode == LAST)
	{
		if (ray->wall_dir == NORTH_WALL || ray->wall_dir == SOUTH_WALL)
		{
			ray->last_angle = atan((double)(distance.x + WALL_LEN) / distance.y) * -1;
		}
		else if (ray->wall_dir == WEST_WALL || ray->wall_dir == EAST_WALL)
		{
			ray->last_angle = atan((double)distance.x / (distance.y - WALL_LEN)) * -1;
		}
	}
}
*/

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
	return (point);
}

static t_point	get_distance_from_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	t_point	begin_distance;
	t_point	last_distance;
	t_point	offset;

	offset = get_offset(ray, FIRST);
	begin_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	begin_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	offset = get_offset(ray, LAST);
	last_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	last_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	//printf("No.0 map_x=%d, map_y=%d, player_x=%d, player_y=%d,dist_x=%d, dist.y=%d \n", cub3d->player->map_x, cub3d->player->map_y,cub3d->player->x, cub3d->player->y, begin_distance.x, begin_distance.y);
	//adjust_begin_distance(cub3d, ray, FIRST);
	//printf("No.1 map_x=%d, map_y=%d, player_x=%d, player_y=%d,dist_x=%d, dist.y=%d \n", cub3d->player->map_x, cub3d->player->map_y,cub3d->player->x, cub3d->player->y, begin_distance.x, begin_distance.y);
	ray->begin_angle = atan((double)begin_distance.x / begin_distance.y);
	ray->last_angle = atan((double)last_distance.x / last_distance.y);
	//printf("No.1 first_x=%d, first_y=%d, last_x=%d, last_y=%d\n", begin_distance.x, begin_distance.y, last_distance.x, last_distance.y);
	//printf("No.2 ray->begin_angle=%lf, ray->last_angle=%lf, ray->wall_dir=%d, dist_x=%d, dist_y=%d\n", ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI, ray->wall_dir , begin_distance.x ,begin_distance.y);
	/*
	if (ray->wall_dir == NORTH_WALL || ray->wall_dir == SOUTH_WALL)
	{
		ray->last_angle = atan((double)(begin_distance.x + WALL_LEN) / begin_distance.y) * -1;
	}
	else if (ray->wall_dir == WEST_WALL || ray->wall_dir == EAST_WALL)
	{
		ray->last_angle = atan((double)begin_distance.x / (begin_distance.y - WALL_LEN)) * -1;
	}
	*/
	if (ray->begin_angle < 0)
		ray->begin_angle += (double)(180 * M_PI / 180);
	if (angle < ray->last_angle)
		ray->last_angle -= (double)(180 * M_PI / 180);
	//printf("No.3 ray->begin_angle=%lf, ray->last_angle=%lf, ray->wall_dir=%d, dist_x=%d, dist_y=%d\n", ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI, ray->wall_dir , begin_distance.x ,begin_distance.y);
	return (begin_distance);
}

static int	get_next_index(t_ray *ray)
{
	return (ray->x + 100);
}

/*
static int	calc_x_len(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	int	i;
	t_cub3d_type	begin_radian;
	t_cub3d_type	last_radian;
	t_cub3d_type	offset_radian;
	//int		x;
	int		max_i;

	max_i = WIN_WIDTH * 360 / FOV;
	offset_radian = (cub3d->player->dir) * M_PI / 180;
	begin_radian = ray->begin_angle - offset_radian;
	last_radian = ray->last_angle - offset_radian;
	//printf("begin_radian=%lf, last=%lf, cos(60)~%lf, cos(420)=%lf\n", begin_radian, last_radian, cos(60 * M_PI / 180), cos(420 * M_PI / 180));
	i = 0;
	while (i < max_i && !(cub3d->angles[i].radian <= begin_radian && begin_radian < cub3d->angles[i + 1].radian))
	{
		//if (i < 150)
			//printf("i=%d, begin_radian=%lf, last=%lf, radian=%lf\n", i,begin_radian, last_radian, cub3d->angles[i].radian);
		i++;
	}
	ray->x = i;
	i = 0;
	while (i < max_i && !(cub3d->angles[i].radian <= last_radian && last_radian < cub3d->angles[i + 1].radian))
		i++;
	ray->x_len = i - cub3d->rays[i].x;
	if (ray->x_len < 0)
		ray->x_len += 800;
	return (0);
}
*/

int	fire_ray(t_cub3d *cub3d, size_t i, t_cub3d_type angle)
{
	static int tmp = 0;
	/*
	cub3d->rays[i].x = i;
	cub3d->rays[i].angle = cub3d->player->dir + cub3d->angles[i];
	cub3d->rays[i].map_point = search_wall(&(cub3d->rays[i]));
	cub3d->rays[i].distance = get_distance_from_wall(cub3d, &(cub3d->rays[i]));
	cub3d->rays[i].wall_img = cub3d->walls->north;
	return (get_next_index(&(cub3d->rays[i])));
	*/

	cub3d->rays[i].x = get_next_index(&(cub3d->rays[i]));
	cub3d->rays[i].map_point = search_wall(&(cub3d->rays[i]));
	//test
	cub3d->rays[i].x = i;
	if (tmp == 5)
	{
		cub3d->rays[i].map_point.x = 4;
		cub3d->rays[i].map_point.y = 1;
		cub3d->rays[i].wall_dir = SOUTH_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->south;
	}
	else if (tmp == 4)
	{
		cub3d->rays[i].map_point.x = 4;
		cub3d->rays[i].map_point.y = 1;
		cub3d->rays[i].wall_dir = WEST_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->west;
	}
	else if (tmp == 3)
	{
		cub3d->rays[i].map_point.x = 3;
		cub3d->rays[i].map_point.y = 0;
		cub3d->rays[i].wall_dir = SOUTH_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->south;
	}
	else if (tmp == 2)
	{
		cub3d->rays[i].map_point.x = 2;
		cub3d->rays[i].map_point.y = 1;
		cub3d->rays[i].wall_dir = SOUTH_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->south;
	}
	else if (tmp == 1)
	{
		cub3d->rays[i].map_point.x = 1;
		cub3d->rays[i].map_point.y = 2;
		cub3d->rays[i].wall_dir = EAST_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->east;
	}
	else if (tmp == 0)
	{
		cub3d->rays[i].map_point.x = 1;
		cub3d->rays[i].map_point.y = 3;
		cub3d->rays[i].wall_dir = EAST_WALL;
		cub3d->rays[i].wall_img = cub3d->walls->east;
	}
	tmp++;
	if (tmp > 3)
		tmp = 0;
	cub3d->rays[i].distance = get_distance_from_wall(cub3d, &(cub3d->rays[i]), angle);
	//calc_x_len(cub3d, &(cub3d->rays[i]), angle);

	//printf("No.2 x=%d, y=%d,dist_x=%d,dist_y=%d, ray->begin_angle=%lf, ray->last_angle=%lf\n",cub3d->rays[i].map_point.x, cub3d->rays[i].map_point.y,cub3d->rays[i].distance.x,cub3d->rays[i].distance.y,  cub3d->rays[i].begin_angle * 180 / M_PI, cub3d->rays[i].last_angle * 180 / M_PI);

	//cub3d->rays[i].x_len = 200;
	return (cub3d->rays[i].x + cub3d->rays[i].x_len);
}
