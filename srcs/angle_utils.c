/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 07:27:31 by hsano             #+#    #+#             */
/*   Updated: 2022/12/29 07:11:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "angle_utils.h"

t_cub3d_type	convt_degree_to_radian(t_cub3d_type val)
{
	t_cub3d_type	tmp;

	tmp = val * M_PI / 180;
	return (tmp);
}

t_cub3d_type	near_angle(t_cub3d_type angle, t_cub3d_type a, t_cub3d_type b)
{
	t_cub3d_type	diff1[3];
	t_cub3d_type	diff2[3];

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
	//printf("angle=%lf, a =%lf,b=%lf, diff1=%lf, diff2=%lf\n", angle* 180 / M_PI, a* 180 / M_PI, b * 180 / M_PI, diff1[2], diff2[2]);
	if (diff1[2] > diff2[2])
		return (b);
	return (a);
}

t_angle	get_radian_per_len(int len)
{
	t_angle	tmp;

	tmp.degree = (t_cub3d_type)len / (WIN_WIDTH - 1);
	tmp.radian = tmp.degree * M_PI / 180;
	return (tmp);
}

t_cub3d_type	distance_to_angle(t_cub3d_type val, t_cub3d_type angle, t_rotate_mode mode)
{
	t_cub3d_type	tmp1;
	t_cub3d_type	tmp2;
	//t_cub3d_type	diff1;
	//t_cub3d_type	diff2;

	//while (angle > M_PI)
		//angle -= M_PI * 2;

	tmp1 = atan(val);
	if (tmp1 < 0)
	{
		tmp2 = tmp1 + 2 * M_PI;
		tmp1 += M_PI;
	}
	else
		tmp2 = tmp1 + M_PI;

	//if (tmp1 < 0)
		//tmp1 += 2 * M_PI;
	//if (tmp1 > M_PI)
	//tmp2 = atan(val) + M_PI;
	printf("distance to angle angle=%lf, tmp1 = %lf, tmp2=%lf\n",angle * 180 / M_PI, tmp1 * 180 / M_PI, tmp2 * 180 / M_PI);
	//tmp2 = fabs(tmp1 - M_PI);
	//diff1 = fabs(angle - tmp1);
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
