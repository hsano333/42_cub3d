/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/17 14:17:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"

int	update_image(t_cub3d *cub3d)
{
	t_matrix	matrix;
	t_xyz		src_xyz;
	t_xyz		dst_xyz;


	/* y-axsis
	matrix.a = 0.866; //cos
	matrix.b = -0.5;
	matrix.c = 0.5;
	matrix.d = 0.866;
	matrix.e = 50;
	matrix.f = 50;
	*/
	matrix.a = 1;
	matrix.b = 0;
	matrix.c = 0;
	//matrix.d = 0.866;
	matrix.d = 0.5;
	matrix.e = 150;
	matrix.f = 150;
	//affine(cub3d, cub3d->walls->south,matrix);
	src_xyz.x = 10;
	src_xyz.y = 10;
	src_xyz.z = 10;
	dst_xyz.x = 800;
	dst_xyz.y = 800;
	dst_xyz.z = 10;
	t_xspace	x_space;
	x_space.x = 0;
	x_space.x_len = 100;
	projective_trans(cub3d, cub3d->walls->south,&matrix, &src_xyz, &dst_xyz, &x_space);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->north->img, 200, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->south->img, 200, 400);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->west->img, 0, 200);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->east->img, 400, 200);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image->img, 0, 0);
	/*
	if (!cub3d->update_image_flag)
		return (false);
	if (cub3d->create_image_flag)
		create_image(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image_info.image, cub3d->offset.x, cub3d->offset.y);
	cub3d->update_image_flag = false;
	cub3d->create_image_flag = false;
	*/
	return (true);
}
