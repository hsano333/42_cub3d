/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:07:40 by hsano             #+#    #+#             */
/*   Updated: 2022/12/16 13:29:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "affine.h"
#include <stdio.h>

t_point calc(t_point src_point, t_matrix matrix)
{
	t_point		point;
	t_point		rpoint;
	long		tmp;

	rpoint.x = 0;
	rpoint.y = 0;
	point.x = matrix.a * src_point.x + matrix.b * src_point.y + matrix.e;
	point.y = matrix.c * src_point.x + matrix.d * src_point.y + matrix.f;
	tmp = (int)nearbyintl(point.x);
	rpoint.x = tmp;
	tmp = (int)nearbyintl(point.y);
	rpoint.y = tmp;
	return (rpoint);
}

void	affine(t_cub3d *cub3d, t_image *src_img, t_matrix matrix)
{
	int	*dst_i;
	int	*src_i;
	t_point	point;
	t_point	affine_point;

	point.y = 0;
	while (point.y < src_img->height)
	{
		point.x = 0;
		while (point.x < src_img->width)
		{
			affine_point = calc(point, matrix);
			if (affine_point.y < cub3d->image->height && affine_point.x < cub3d->image->width)
			{
				dst_i = cub3d->image->addr + (cub3d->image->sl * (affine_point.y));
				src_i = src_img->addr + (src_img->sl * (point.y));
				dst_i[affine_point.x] = src_i[point.x];
			}
			(point.x)++;
		}
		(point.y)++;
	}
}
