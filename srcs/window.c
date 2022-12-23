/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/23 06:34:22 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"
#include "ray.h"
#include "close.h"

int	update_image_per_x(t_cub3d *cub3d, int x, t_cub3d_type z, t_ray *ray, t_cub3d_type angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;

	y = z;
	y = 0;

	img_point.x = (int)((((((x - ray->begin_x) * (WALL_LEN - ray->img_offset_x) / (ray->last_x - ray->begin_x)))) + (ray->img_offset_x)) * ray->wall_img->width / WALL_LEN);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		//img_point.y = y;
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		//img_point.y = (int)nearbyintl((double)y * (tan(angle) / (double)img_point.x  ) * WIN_HEIGHT / ray->wall_img->height) * 50 ;
		if ((0 < angle && angle < 0.1 * M_PI / 180) || (179.9999 * M_PI / 180 < angle && angle < 180.0001 * M_PI / 180))
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.y / ray->wall_img->height);
		else if ((89.99999 * M_PI / 180 < angle && angle < 90.000001 * M_PI / 180) && (269.99999  * M_PI / 180 < angle && angle < 270.000001 * M_PI / 180))
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.x / ray->wall_img->height);
		else
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.x / tan(angle) / ray->wall_img->height);
		if (x > 650 && y == 10)
			printf("x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
		//img_point.y = y;
		if (0 <= img_point.y && img_point.y < ray->wall_img->height && 0 <= img_point.x && img_point.x < ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
		{
			win_img_addr[x] = 0;
			if (y == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
			//if (y == 100)
				//printf("blank x=%d, img_point.x=%d, img_point.y=%d\n", x, img_point.x, img_point.y);

		}
		else
		{
			win_img_addr[x] = 255;
			if (y == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d,ray->begin_x=%d, ray->last_x=%d  \n", x, img_point.x, y, img_point.y, ray->begin_x, ray->last_x);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
		}

		y++;
	}
	return (true);
}


int	update_image(t_cub3d *cub3d)
{
	//t_matrix	matrix;
	//t_xyz		src_xyz;
	//t_xyz		dst_xyz;
	int		i;
	//size_t		next_i;
	int		j;
	//t_point		map_point;
	t_cub3d_type	z;
	t_cub3d_type	angle;

	//map_point.x = 0;
	i = 0;
	//next_i = 0;
	j = 0;

	//affine(cub3d, cub3d->walls->south,matrix);
	//src_xyz.x = 10;
	//src_xyz.y = 10;
	//src_xyz.z = 10;
	//dst_xyz.x = 800;
	//dst_xyz.y = 800;
	//dst_xyz.z = 10;
	//t_xspace	x_space;
	//x_space.x = 0;
	//x_space.x_len = 100;

	cub3d->player->map_x = 2;
	cub3d->player->map_y = 3;
	cub3d->player->x = 100;
	cub3d->player->y = 100;
	cub3d->player->dir = 0;
	
	//map_point = cub3d->rays[j].map_point;
	//printf("map_point=%d\n", map_point.x);
	cub3d->rays[j].last_angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[0].radian) + 1;
	//printf("No.0 angle\n");
	cub3d->rays[0].last_x = -1;
	int tmp = 0;
	while (i < WIN_WIDTH)
	{
		angle = (cub3d->player->dir * M_PI / 180 + cub3d->angles[i].radian);
		if (angle > 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		//if (angle > cub3d->rays[j].begin_angle)
			//angle -= 360 * M_PI / 180;
		//if (is_next_wall(&(cub3d->rays[j]), angle))
		if (i >= cub3d->rays[j].last_x)
		{
			printf("fire renew i=%d, j=%d, angle=n%lf\n", i, j, angle * 180 / M_PI);
			//printf("No.1 angle =%lf,cub3d->rays[j].last_angle=%lf i=%ld, j=%ld\n", angle,cub3d->rays[j].last_angle, i, j);
			j = i;
			tmp = fire_ray(cub3d, i, angle, tmp);
			//printf("No.2 angle =%lf,cub3d->rays[j].last_angle=%lf i=%ld, j=%ld\n", angle,cub3d->rays[j].last_angle, i, j);
		}
		z = tan(cub3d->rays[j].begin_angle);
		//printf("cub3d->player->dir=%d, angle[%zu]=%f, angle=%f\n", cub3d->player->dir,i, cub3d->angles[i], angle);
		update_image_per_x(cub3d, i, z, &cub3d->rays[j], angle);
		i++;
	}
	//printf("No.3 angle =%lf,cub3d->rays[j].last_angle=%lf i=%ld, j=%ld\n", angle,cub3d->rays[j].last_angle, i, j);
	//projective_trans(cub3d, cub3d->walls->south,&matrix, &src_xyz, &dst_xyz, &x_space);
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
	//error_and_end_game(cub3d, "cub3D:failure to init minilix\n");
	return (true);
}
