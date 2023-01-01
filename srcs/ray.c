/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2023/01/01 07:37:31 by hsano            ###   ########.fr       */
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

	//printf("next_map.x=%d, next_map.y=%d,   map.x=%d, map.y=%d \n", next_map.x, next_map.y, map.x, map.y);
	if (diff_y == -1)
	{
		printf("south\n");
		ray->wall_dir = SOUTH_WALL;
		ray->wall_img = cub3d->walls->north;
	}
	else if (diff_y == 1)
	{
		printf("north\n");
		ray->wall_dir = NORTH_WALL;
		ray->wall_img = cub3d->walls->south;
	}
	else if (diff_x == 1)
	{
		printf("west\n");
		ray->wall_dir = WEST_WALL;
		ray->wall_img = cub3d->walls->east;
	}
	else if (diff_x == -1)
	{
		printf("east\n");
		ray->wall_dir = EAST_WALL;
		ray->wall_img = cub3d->walls->west;
	}
}

static	t_point search_wall(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle, t_point map)
{
	t_cub3d_type	y_dist;
	t_cub3d_type	x_dist;
	t_point		next;

	//printf("search wall No.1 map.x=%d, map.y=%d, angle=%lf\n", map.x, map.y, angle * 180 / M_PI);
	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		y_dist = cub3d->player->world_y - map.y * WALL_LEN;
	else
		//y_dist = cub3d->player->world_y - (map.y + 1) * WALL_LEN;
		y_dist = (map.y + 1) * WALL_LEN - cub3d->player->world_y;
		//y_dist = (map.y + 1) * WALL_LEN - cub3d->player.world_y;
	if (angle < M_PI && angle > 0)
		x_dist = cub3d->player->world_x - map.x * WALL_LEN;
	else
		//x_dist = cub3d->player->world_x - (map.x + 1) * WALL_LEN;
		x_dist = (map.x + 1) * WALL_LEN - cub3d->player->world_x;
	//printf("search wall No.2 x_dist=%lf, y_dist=%lf, y_dist*tan(an)=%lf\n", x_dist, y_dist, y_dist * tan(angle));
	next = next_map_mass(angle, x_dist, y_dist, map);
	//printf("search wall No.3 next:map.x=%d, map.y=%d, angle=%lf\n", next.x, next.y, angle * 180 / M_PI);
	if (cub3d->map[next.y][next.x].obj == WALL || cub3d->map[next.y][next.x].obj >= DOOR)
	{
		set_map_dir(cub3d, ray, map, next);
		return (next);
	}
	//printf("search wall No.4 next.x=%d, next.y=%d\n", next.x, next.y);
	return (search_wall(cub3d, ray, angle, next));
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
	else if (ray->wall_dir == WEST_WALL)
		point.y = 1;
	return (point);
}

int	is_next_wall(t_ray *ray, t_cub3d_type angle)
{
	//printf("is_next_wall No.2, ray->begin_angle=%lf, ray->last_angle=%lf, angle=%lf\n", ray->begin_angle * 180 / M_PI, ray->last_angle * 180 / M_PI, angle * 180 / M_PI);
	if (ray->begin_angle >= ray->last_angle && angle < ray->last_angle)
		return (true);
	else if (ray->begin_angle < ray->last_angle)
	{
		if (angle > ray->begin_angle && angle < ray->last_angle)
			return (true);
	}
	//printf("is_next_wall No.3\n");
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
	//printf("ray=%p, ray->begin_distance=%p\n", ray, &(ray->begin_distance.x));
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
	//if (isnan(pre_last_angle))
	ray->begin_angle = distance_to_angle((double)begin_distance.x / begin_distance.y, angle, RORATE_PLUS);
	//else
		//ray->begin_angle = pre_last_angle;
	ray->last_angle = distance_to_angle((double)last_distance.x / last_distance.y, angle, RORATE_MINUS);
	ray->base_angle = angle;

	/*
	int tmp;
	//if (cub3d->player->dir.radian >= M_PI * 7 / 4 || cub3d->player->dir.radian < M_PI / 4)
	//{
//
	//}
	if (cub3d->player->dir.radian >= M_PI  / 4 && cub3d->player->dir.radian < M_PI * 3 / 4)
	{
		tmp = begin_distance.x;
		begin_distance.x = begin_distance.y;
		begin_distance.y = tmp;
		tmp = last_distance.x;
		last_distance.x = last_distance.y;
		last_distance.y = tmp;
	}
	//else if (cub3d->player->dir.radian >= M_PI * 3 / 4 || cub3d->player->dir.radian < M_PI * 5 / 4)
	//{
	//}
	else if (cub3d->player->dir.radian >= M_PI * 5 / 4 && cub3d->player->dir.radian < M_PI * 7 / 4)
	{
		tmp = begin_distance.x;
		begin_distance.x = begin_distance.y;
		begin_distance.y = tmp;
		tmp = last_distance.x;
		last_distance.x = last_distance.y;
		last_distance.y = tmp;

	}
	*/
	//else
		//ray->base_angle = pre_last_angle;
	//ray->x_len = (fabs(ray->last_angle - ray->begin_angle) * 180 / M_PI) * (WIN_WIDTH + 1) / FOV;
	//ray->x_len = (int)((fabs(ray->last_angle - angle) * 180 / M_PI) * (WIN_WIDTH - 1) / FOV);
	//while (i < WIN_WIDTH && is_next_wall(ray, angle))
	//{
		//angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[++i].radian);
		//if (angle > 360 * M_PI / 180)
			//angle -= 360 * M_PI / 180;
		//printf("last:i=%ld, angle=%lf, degree=%lf\n", i, angle, angle*180 / M_PI);
	//}
	//ray->last_x = --i;
	ray->begin_x = ray->x;
	//ray->last_x = ray->x + ray->x_len;
	//double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) * ray->wall_img->width / (WALL_LEN * WALL_LEN);
	//double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) * ray->wall_img->width / (WALL_LEN * WALL_LEN);
	//double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) * ray->wall_img->width / (WALL_LEN * WALL_LEN);
	//double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) * ray->wall_img->height / (WALL_LEN * WALL_LEN);
	double base_x = (begin_distance.x / tan(ray->last_angle) - begin_distance.x / tan(ray->begin_angle)) / WALL_LEN;
	double base_y = (begin_distance.y * tan(ray->last_angle) - begin_distance.y * tan(ray->begin_angle)) / WALL_LEN;
	if (begin_distance.x == last_distance.x)
	{
		ray->img_offset_begin = ((begin_distance.x / tan(angle) - begin_distance.x / tan(ray->begin_angle)) * base_x);
		ray->img_offset_last = cub3d->player->y;
	}
	else
	{
		ray->img_offset_begin = ((begin_distance.y * tan(angle) - begin_distance.y * tan(ray->begin_angle)) * base_y);
		ray->img_offset_last = cub3d->player->x;
	}
	printf("\nray No.1 angle=%lf, ray calcing offset:ray->img_offset_begin=%lf, ray->img_offset_last=%lf\n",angle * 180 / M_PI, ray->img_offset_begin, ray->img_offset_last );
	printf("ray No.2 ray->begin_angle=%lf, ray->base_angle=%lf, ray->last_angle=%lf, \n", ray->begin_angle * 180 / M_PI, ray->base_angle * 180 / M_PI, ray->last_angle * 180 / M_PI); 
	printf("ray No.3 begin_distance.x=%d, begin_distance.y=%d, last_distance.x=%d, last_distance.y=%d\n", begin_distance.x, begin_distance.y, last_distance.x, last_distance.y);
	if (ray->x != 0)
		ray->img_offset_begin = 0;
	//if (ray->last_x < WIN_WIDTH)
		//ray->img_offset_last = 0;
	//if (ray->last_x > WIN_WIDTH)
		//ray->last_x = WIN_WIDTH;
	//while (ray->img_offset_begin >= WALL_LEN)
		//ray->img_offset_begin -= WALL_LEN;
	//if (ray->last_x >= WIN_WIDTH)
		//ray->last_x = WIN_WIDTH;
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
	if (ray->last_angle < 0)
		ray->last_angle += (double)(360 * M_PI / 180);
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

int	fire_ray(t_cub3d *cub3d, t_ray *ray, t_cub3d_type angle)
{
	//printf("\nfire_ray test No.1, , angle=%lf \n",  angle * 180 / M_PI);
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
	//printf("\nsearch wall start i=%zu, angle=%lf\n", i, angle * 180 / M_PI);
	/*
	for(int k = 0; k<= 6;k++)
	{
		for(int j = 0; j<= 6;j++)
		{
			printf("%d", cub3d->map[k][j].obj);
		}
		printf("\n");
	}
	*/

			//cub3d->map[i][j] = map_cell;
	//ray->map_point = search_wall(cub3d, ray, convert_positive_radian(angle), get_player_map_point(cub3d));
	ray->map_point = search_wall(cub3d, ray, angle, get_player_map_point(cub3d));
	//set_map_dir(cub3d, ray);
	printf("ray No.2 searched map x=%d, y=%d, angle=%lf\n", ray->map_point.x, ray->map_point.y, angle * 180 / M_PI);
	//set_wall();


	//test
	//ray->x = i;
		//ray->map_point.x = 7;
		//ray->map_point.y = 1;
		//ray->wall_dir = SOUTH_WALL;
		//ray->wall_img = cub3d->walls->south;

	ray->distance = get_distance_from_wall(cub3d, ray, angle);
	//printf("ray No.3 ray->img_offset_begin=%lf, ray->img_offset_last=%lf\n", ray->img_offset_begin, ray->img_offset_last);
	return (true);
}
