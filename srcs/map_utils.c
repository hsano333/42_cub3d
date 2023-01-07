/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:49:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 17:48:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_utils.h"
#include <float.h>
#include <stdlib.h>

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

t_point	get_player_map_point(t_cub3d *cub3d)
{
	t_point	point;

	point.x = cub3d->player->map.x;
	point.y = cub3d->player->map.y;
	return (point);
}

t_cub3d_type	convert_positive_radian(t_cub3d_type radian)
{
	if (radian < 0)
		return (radian + 2 * M_PI);
	return (radian);
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
