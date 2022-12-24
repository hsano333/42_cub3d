/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2022/12/24 08:42:59 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "angle_utils.h"

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

int	is_next_wall(t_ray *ray, t_cub3d_type angle)
{
	if (ray->begin_angle >= ray->last_angle && angle < ray->last_angle)
		return (true);
	else if (ray->begin_angle < ray->last_angle)
	{
		if (angle > ray->begin_angle && angle < ray->last_angle)
			return (true);
	}
	return (false);
}

static t_point	get_distance_from_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	t_point	begin_distance;
	t_point	last_distance;
	t_point	offset;
	//size_t	i;

	offset = get_offset(ray, FIRST);
	begin_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	begin_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	//safe
	printf("ray=%p, ray->begin_distance=%p\n", ray, &(ray->begin_distance.x));
	//ray->begin_distance.x = begin_distance.x;
	//ray->begin_distance.y = 1;
	//return (offset);
	ray->begin_distance = begin_distance;
	//out
	offset = get_offset(ray, LAST);
	//out
	last_distance.x = ((int)((cub3d->player->map_x - (ray->map_point.x + offset.x))) * WALL_LEN + cub3d->player->x);
	last_distance.y = ((int)((cub3d->player->map_y - (ray->map_point.y + offset.y))) * WALL_LEN + cub3d->player->y);
	ray->last_distance = last_distance;
	//out
	//
	//ray->begin_angle = atan((double)begin_distance.x / begin_distance.y);
	//ray->last_angle = atan((double)last_distance.x / last_distance.y);
	//ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, ray->last_angle);
	//ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, ray->begin_angle);
	//ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, angle);
	//ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle);
	ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, angle, RORATE_PLUS);
	ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle, RORATE_MINUS);
	//ray->x_len = (fabs(ray->last_angle - ray->begin_angle) * 180 / M_PI) * (WIN_WIDTH + 1) / FOV;
	ray->x_len = (int)((fabs(ray->last_angle - angle) * 180 / M_PI) * (WIN_WIDTH + 1) / FOV);
	//while (i < WIN_WIDTH && is_next_wall(ray, angle))
	//{
		//angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[++i].radian);
		//if (angle > 360 * M_PI / 180)
			//angle -= 360 * M_PI / 180;
		//printf("last:i=%ld, angle=%lf, degree=%lf\n", i, angle, angle*180 / M_PI);
	//}
	//ray->last_x = --i;
	ray->begin_x = ray->x;
	ray->last_x = ray->x + ray->x_len;
	//double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) * ray->wall_img->width / (WALL_LEN * WALL_LEN);
	//double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) * ray->wall_img->width / (WALL_LEN * WALL_LEN);
	double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) / WALL_LEN;
	double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) / WALL_LEN;
	if (begin_distance.x == last_distance.x)
	{
		ray->img_offset_begin = fabs(nearbyintl((begin_distance.x / tan(angle) - begin_distance.x / tan(ray->begin_angle)) * base_x));
		ray->img_offset_last = cub3d->player->y;
	}
	else
	{
		ray->img_offset_begin = fabs(nearbyintl((begin_distance.y * tan(angle) - begin_distance.y * tan(ray->begin_angle)) * base_y));
		ray->img_offset_last = cub3d->player->x;
	}
	//
	if (ray->x != 0)
		ray->img_offset_begin = 0;
	if (ray->last_x < WIN_WIDTH)
		ray->img_offset_last = 0;
	if (ray->last_x > WIN_WIDTH)
		ray->last_x = WIN_WIDTH;
	//while (ray->img_offset_begin >= WALL_LEN)
		//ray->img_offset_begin -= WALL_LEN;
	//if (ray->last_x >= WIN_WIDTH)
		//ray->last_x = WIN_WIDTH;
	//printf("last 0:i=%ld, angle=%lf, degree=%lf, begin_angle=%lf, last_angle=%lf, last_distance.x=%d, last_distance.x=%d, begin_x=%d, last_x=%d,, ray->x_len=%d\n", i, angle, angle*180 / M_PI, ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI ,last_distance.x, last_distance.y, ray->begin_x, ray->last_x, ray->x_len);
	//ray->img_offset_begin = (int)(nearbyintl(ray->wall_img->width * (x - ray->begin_x) / (ray->last_x - ray->begin_x)));
	/*
	if (ray->begin_angle < 0)
		ray->begin_angle += (double)(360 * M_PI / 180);
	if (ray->begin_angle > 360)
		ray->begin_angle -= (double)(360 * M_PI / 180);
	if (ray->last_angle < 0)
		ray->last_angle += (double)(360 * M_PI / 180);
	if (ray->last_angle > 360)
		ray->last_angle -= (double)(360 * M_PI / 180);
	*/
	//i = ray->x;
	//printf("begin 0:i=%ld, angle=%lf, degree=%lf\n", i, angle, angle*180 / M_PI);
	/*
	while (is_next_wall(ray, angle))
	{
		angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[--i].radian);
		if (angle > 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		printf("begin:i=%ld, angle=%lf, degree=%lf\n", i, angle, angle*180 / M_PI);
	}
	*/
	/*
	ray->begin_x = ++i;
	angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[i].radian);
	printf("last 0:i=%ld, angle=%lf, degree=%lf, begin_angle=%lf, last_angle=%lf, last_distance.x=%d, last_distance.x=%d\n", i, angle, angle*180 / M_PI, ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI ,last_distance.x, last_distance.y);
	while (i < WIN_WIDTH && is_next_wall(ray, angle))
	{
		angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[++i].radian);
		if (angle > 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		printf("last:i=%ld, angle=%lf, degree=%lf\n", i, angle, angle*180 / M_PI);
	}
	ray->last_x = --i;
	*/
	return (begin_distance);
}

/*
static int	get_next_index(t_ray *ray)
{
	return (ray->x + 100);
}
*/

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
	ray->x_len = i - ray->x;
	if (ray->x_len < 0)
		ray->x_len += 800;
	return (0);
}
*/

int	fire_ray(t_cub3d *cub3d, t_ray *ray, size_t i, t_cub3d_type angle, int tmp)
{
	printf("fire_ray test No.1, i=%zu, ray=%p , tmp=%d\n", i, ray, tmp);
	//int tmp = 0;
	/*
	ray->x = i;
	ray->angle = cub3d->player->dir + cub3d->angles[i];
	ray->map_point = search_wall(&(cub3d->rays[i]));
	ray->distance = get_distance_from_wall(cub3d, &(cub3d->rays[i]));
	ray->wall_img = cub3d->walls->north;
	return (get_next_index(&(cub3d->rays[i])));
	*/

	//ray->x = get_next_index(&(cub3d->rays[i]));
	ray->map_point = search_wall(ray);
	//test
	ray->x = i;
	if (tmp == 7)
	{
		ray->map_point.x = 7;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 6)
	{
		ray->map_point.x = 6;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 5)
	{
		ray->map_point.x = 5;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 4)
	{
		ray->map_point.x = 4;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 3)
	{
		ray->map_point.x = 3;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 2)
	{
		ray->map_point.x = 2;
		ray->map_point.y = 1;
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 1)
	{
		ray->map_point.x = 1;
		ray->map_point.y = 2;
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->east;
		//
		//ray->map_point.x = 1;
		//ray->map_point.y = 1;
		//ray->wall_dir = SOUTH_WALL;
		//ray->wall_img = cub3d->walls->south;
	}
	else if (tmp == 0)
	{
		ray->map_point.x = 1;
		ray->map_point.y = 3;
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->east;
		//
		//ray->map_point.x = 0;
		//ray->map_point.y = 1;
		//ray->wall_dir = SOUTH_WALL;
		//ray->wall_img = cub3d->walls->south;
	}
	//tmp++;
	//if (tmp > 7 || ray->last_x == 800)
	//if (tmp > 4 || ray->last_x == 800)
		//tmp = 0;
	printf("fire_ray test No.2\n");
	ray->distance = get_distance_from_wall(cub3d, ray, angle);
	printf("fire_ray test No.3\n");
	//calc_x_len(cub3d, &(cub3d->rays[i]), angle);

	//printf("No.2 x=%d, y=%d,dist_x=%d,dist_y=%d, ray->begin_angle=%lf, ray->last_angle=%lf, angle=%lf,begin=%d,last_x =%d ,ray->img_offset_begin=%lf , ray->wall_img->width=%d, tmp=%d, begin_distance.x=%d, begin_distance.y=%d, ray->img_offset_last=%lf\n",ray->map_point.x, ray->map_point.y,ray->distance.x,ray->distance.y,  ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI, angle * 180 / M_PI, ray->begin_x, ray->last_x, ray->img_offset_begin, ray->wall_img->width,tmp, ray->distance.x, ray->distance.y, ray->img_offset_last);

	//ray->x_len = 200;
	return (tmp + 1);
}
