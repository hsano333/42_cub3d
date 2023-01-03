/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:49:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/03 18:16:43 by hsano            ###   ########.fr       */
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

//t_point next_map_mass(t_cub3d_type angle, t_cub3d_type x_dist, t_cub3d_type y_dist, t_point map)
t_point next_map_mass(t_cub3d_type angle, t_point point, t_point map)
{
	//int	x_len;
	//int	y_len;
	double a;
	double b;

	if (fabs(angle - 0) <= D_EQUAL)
		return (add_map_point(map, 0, -1));
	else if (fabs(angle - (M_PI / 2)) <= D_EQUAL)
		return (add_map_point(map, -1, 0));
	else if (fabs(angle - (M_PI)) <= D_EQUAL)
		return (add_map_point(map, 0, 1));
	else if (fabs(angle - (M_PI * 3 / 2)) <= D_EQUAL)
		return (add_map_point(map, 1, 0));
	a = 1 / tan(angle);
	b = (double)point.y - a * (double)point.x;

	//printf("error next map, angle=%lf, a=%lf, b=%lf, b/a=%lf, point.x=%d, point.y=%d\n", angle * 180 / M_PI , a, b, -b/a, point.x, point.y);
	//y = ax + b;
	if (angle <= M_PI / 2)
	{
		if ((-b / a >= -D_EQUAL) && (-b / a <= WALL_LEN))
			return (add_map_point(map, 0, -1));
		else
			return (add_map_point(map, -1, 0));
	}
	else if (angle <= M_PI)
	{
		if (angle <= M_PI && b >= -D_EQUAL && -D_EQUAL <= b && b <= WALL_LEN)
			return (add_map_point(map, -1, 0));
		else
			return (add_map_point(map, 0, 1));
	}
	else if (angle <= M_PI * 3 / 2)
	{
		if (((WALL_LEN - b) / a >= -D_EQUAL) && ((WALL_LEN - b)/ a <= WALL_LEN))
			return (add_map_point(map, 0, 1));
		else
			return (add_map_point(map, 1, 0));
	}
	if ((-D_EQUAL <= (WALL_LEN * a + b)) && ((WALL_LEN * a + b) <= WALL_LEN))
		return (add_map_point(map, 1, 0));
	return (add_map_point(map, 0, -1));


	if (angle <= M_PI / 2 && angle >= M_PI * 3 / 2 && (-b / a >= 0) && (-b / a <= WALL_LEN))
	{
		//printf("next north\n");
		return (add_map_point(map, 0, -1));
	}
	else if (angle >= M_PI / 2 && angle <= M_PI * 3 / 2 && ((WALL_LEN - b) / a >= 0) && ((WALL_LEN - b)/ a <= WALL_LEN))
	{
		//printf("next south\n");
		return (add_map_point(map, 0, 1));
	}
	else if (angle <= M_PI && b >= 0 && 0 <= b && b <= WALL_LEN)
	{
		//printf("next west\n");
		return (add_map_point(map, -1, 0));
	}
	else if (angle >= M_PI && (0 <= (WALL_LEN * a + b)) && ((WALL_LEN * a + b) <= WALL_LEN))
	{
		//printf("next east\n");
		return (add_map_point(map, 1, 0));
	}
	//printf("error next map, angle=%lf, a=%lf, b=%lf\n", angle * 180 / M_PI , a, b);
	exit(1);



	/*
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
	*/
	return (add_map_point(map, 0, -1));
}

t_cub3d_type	convert_positive_radian(t_cub3d_type radian)
{
	if (radian < 0)
		return (radian + 2 * M_PI);
	return (radian);
}

t_point	get_wall_distance_from_player(t_cub3d *cub3d, t_point map_point, t_point offset)
{
	t_point distance;

	distance.x = ((int)((cub3d->player->map.x - (map_point.x + offset.x))) * WALL_LEN + cub3d->player->mass.x);
	distance.y = ((int)((cub3d->player->map.y - (map_point.y + offset.y))) * WALL_LEN + cub3d->player->mass.y);
	return (distance);
}
