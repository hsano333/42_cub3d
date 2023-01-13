/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:49:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 20:17:03 by hsano            ###   ########.fr       */
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
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

double	convert_positive_radian(double radian)
{
	if (radian < 0)
		return (radian + 2 * M_PI);
	return (radian);
}

t_point	get_wall_distance_from_player(t_cub3d *cub3d \
									, t_point map_point, t_point offset)
{
	t_point	distance;
	int	world_x;
	int	world_y;

	world_x = (cub3d->player->map.x - (map_point.x + offset.x)) * WALL_LEN;
	world_y = (cub3d->player->map.y - (map_point.y + offset.y)) * WALL_LEN;
	distance.x = world_x + cub3d->player->mass.x;
	distance.y = world_y + cub3d->player->mass.y;
	return (distance);
}

void	set_map_dir(t_cub3d *cub3d, t_ray *ray \
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
