/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:13:20 by hsano             #+#    #+#             */
/*   Updated: 2022/12/18 14:24:58 by hsano            ###   ########.fr       */
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

static t_point	get_distance_from_wall(t_cub3d *cub3d, t_ray *ray)
{
	t_point	distance;

	distance.x = ((int)(fabs(ray->map_point.x - cub3d->player->map_x)) * WALL_LEN - cub3d->player->x * WALL_LEN / MAP_SPACE);
	distance.y = ((int)(fabs(ray->map_point.y - cub3d->player->map_y)) * WALL_LEN - cub3d->player->y * WALL_LEN / MAP_SPACE);
	//distance.z = ((int)(fabs(ray->map_point.y - cub3d->player->map_y)) * WALL_LEN - cub3d->player->y);
	return (distance);
}

static	int get_next_index(t_ray *ray)
{
	return (ray->x + 100);
}

int	fire_ray(t_cub3d *cub3d, size_t i)
{
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
	cub3d->rays[i].angle = cub3d->player->dir + cub3d->angles[i];
	if (i > 600)
	{
		cub3d->rays[i].map_point.x = 4;
		cub3d->rays[i].map_point.y = 0;
	}
	else if (i > 400)
	{
		cub3d->rays[i].map_point.x = 3;
		cub3d->rays[i].map_point.y = 0;
	}
	else if (i > 200)
	{
		cub3d->rays[i].map_point.x = 2;
		cub3d->rays[i].map_point.y = 0;
	}
	else
	{
		cub3d->rays[i].map_point.x = 1;
		cub3d->rays[i].map_point.y = 2;
	}
	cub3d->rays[i].distance = get_distance_from_wall(cub3d, &(cub3d->rays[i]));
	cub3d->rays[i].wall_img = cub3d->walls->north;
	return (cub3d->rays[i].x + 200);
}
