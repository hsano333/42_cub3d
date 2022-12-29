/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:49:47 by hsano             #+#    #+#             */
/*   Updated: 2022/12/29 08:52:37 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_utils.h"
#include <float.h>
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