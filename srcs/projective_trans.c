/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projective_trans.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:31:40 by hsano             #+#    #+#             */
/*   Updated: 2022/12/18 14:28:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projective_trans.h"
#include <stdio.h>

static t_point calc(t_point *src_point, t_matrix *matrix, t_xyz *src_xyz, t_xyz *dst_xyz, t_xspace *x_space)
{
	t_point		point;
	t_point		rpoint;
	long		tmp;
	int	x;
	int	y;

	rpoint.x = x_space->x;
	rpoint.y = dst_xyz->x;

	x = (2 * (src_point->z + src_point->x) * src_point->x) / WALL_LEN  + (src_xyz->x) / WALL_LEN + 200;
	y = (2 * (src_point->z + src_point->x) * src_point->y) / WALL_LEN + (src_xyz->y) / WALL_LEN + 200;

	point.x = matrix->a * src_point->x + matrix->b * src_point->y + matrix->e;
	point.y = matrix->c * src_point->x + matrix->d * src_point->y + matrix->f;
	point.x = matrix->a * src_point->x + matrix->b * src_point->y + matrix->e;
	point.y = matrix->c * src_point->x + matrix->d * src_point->y + matrix->f;
	
	tmp = (int)nearbyintl(point.x);
	rpoint.x = tmp;
	rpoint.x = x;
	tmp = (int)nearbyintl(point.y);
	rpoint.y = tmp;
	rpoint.y = y;
	return (rpoint);
}

void	projective_trans(t_cub3d *cub3d, t_image *src_img, t_matrix *matrix, t_xyz *src_xyz, t_xyz *dst_xyz, t_xspace *x_space)
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
			affine_point = calc(&point, matrix, src_xyz, dst_xyz, x_space);
			if (0 <= affine_point.y && affine_point.y < cub3d->image->height && 0 <= affine_point.x && affine_point.x < cub3d->image->width)
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
