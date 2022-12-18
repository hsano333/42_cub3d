/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/18 14:29:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"
#include "ray.h"

int	update_image_per_x(t_cub3d *cub3d, int x, t_cub3d_type z, t_ray *ray, t_cub3d_type angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;

	y = z;
	y = 0;
	img_point.x = x;
	//img_point.x = (int)(nearbyintl(tan(angle) * ray->distance.x - (ray->map_point.x - cub3d->player->map_x) * WALL_LEN) / WALL_LEN) * ray->wall_img->width / WALL_LEN;
	printf("x = %d, angle=%f,ray->distance.x=%d, img_point.x=%d\n ", x,angle, ray->distance.x, img_point.x);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		img_point.y = y;
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
		if (0 <= img_point.y && img_point.y < ray->wall_img->height && 0 <= img_point.x && img_point.x < ray->wall_img->width)
		{
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
			win_img_addr[x] = 0;
		else
			win_img_addr[x] = 255;
		y++;
	}
	return (true);
}

int	update_image(t_cub3d *cub3d)
{
	t_matrix	matrix;
	t_xyz		src_xyz;
	t_xyz		dst_xyz;
	size_t		i;
	size_t		next_i;
	size_t		j;
	//t_point		map_point;
	t_cub3d_type	z;
	t_cub3d_type	angle;

	//map_point.x = 0;
	i = 0;
	next_i = 0;
	j = 0;

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

	cub3d->player->map_x = 3;
	cub3d->player->map_y = 3;
	cub3d->player->x = 10;
	cub3d->player->y = 10;
	
	//map_point = cub3d->rays[j].map_point;
	//printf("map_point=%d\n", map_point.x);
	while (i < WIN_WIDTH)
	{
		if (i == next_i)
		{
			j = i;
			next_i = fire_ray(cub3d, i);
		}
		z = tan(cub3d->rays[j].angle);
		angle = cub3d->player->dir + cub3d->angles[i];
		//printf("cub3d->player->dir=%d, angle[%zu]=%f, angle=%f\n", cub3d->player->dir,i, cub3d->angles[i], angle);
		update_image_per_x(cub3d, i, z, &cub3d->rays[j], angle);
		i++;
	}
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
