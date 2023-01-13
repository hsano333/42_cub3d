/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 07:27:31 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 20:16:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "angle_utils.h"

double	fit_in_radian(double angle)
{
	if (angle >= 360 * M_PI / 180)
		angle -= 360 * M_PI / 180;
	else if (angle < 0)
		angle += 360 * M_PI / 180;
	return (angle);
}

/*
double	convt_degree_to_radian(double val)
{
	double	tmp;

	tmp = val * M_PI / 180;
	return (tmp);
}
*/

/*
double	near_angle(double angle, double a, double b)
{
	double	diff1[3];
	double	diff2[3];

	diff1[0] = fabs(a - angle);
	diff1[1] = 2 * M_PI - fabs(a - angle);
	if (diff1[0] > diff1[1])
		diff1[2] = diff1[1];
	else
		diff1[2] = diff1[0];
	diff2[0] = fabs(b - angle);
	diff2[1] = 2 * M_PI - fabs(b - angle);
	if (diff2[0] > diff2[1])
		diff2[2] = diff2[1];
	else
		diff2[2] = diff2[0];
	if (diff1[2] > diff2[2])
		return (b);
	return (a);
}
*/

/*
t_angle	get_radian_per_len(int len)
{
	t_angle	tmp;

	tmp.degree = (double)len / (WIN_WIDTH - 1);
	tmp.radian = tmp.degree * M_PI / 180;
	return (tmp);
}
*/

double	distance_to_angle(double val \
					, double angle, t_rotate_mode mode)
{
	double	tmp1;
	double	tmp2;

	tmp1 = atan(val);
	if (tmp1 < 0)
	{
		tmp2 = tmp1 + 2 * M_PI;
		tmp1 += M_PI;
	}
	else
		tmp2 = tmp1 + M_PI;
	if (mode == RORATE_PLUS)
	{
		if (tmp1 >= angle)
			return (tmp1);
		else if (tmp2 >= angle)
			return (tmp2);
		else
			return (tmp1);
	}
	if (angle > tmp2)
		return (tmp2);
	if (angle > tmp1)
		return (tmp1);
	return (tmp2);
}

int	is_in_range_fov(t_cub3d *cub3d, double angle)
{
	angle -= cub3d->player->dir.radian;
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > M_PI && angle >= cub3d->angles[WIN_WIDTH - 1].radian)
		return (true);
	else if (angle < M_PI && angle <= cub3d->angles[0].radian)
		return (true);
	return (false);
}
