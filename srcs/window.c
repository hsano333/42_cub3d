/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/29 05:41:52 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"
#include "ray.h"
#include "close.h"
#include "libft_mem.h"

int	update_image_per_x(t_cub3d *cub3d, int x, int img_x_offset, t_ray *ray, t_cub3d_type angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;
	//t_cub3d_type offset = (ray->distance.x / tan(angle)) / 2 - WALL_LEN;
	t_cub3d_type z = 0;
	t_cub3d_type ratio = 0;
	t_cub3d_type tan_val;
	//t_cub3d_type far_height;

	y = z;
	y = 0;

	tan_val = fabs(tan(ray->base_angle));
	if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN || tan(ray->base_angle) == NAN)
		z = ray->begin_distance.y;
	else
		z = ray->last_distance.y / tan_val;
	ratio = z / BASE_ZX;
	img_point.x = (int)((((x - img_x_offset) * ratio) + ray->img_offset_begin) * ray->wall_img->width / WALL_LEN);
	//printf("No.1 img_point.x=%d,ray->wall_img->width=%d, x=%d,img_x_offset=%d,ratio=%lf, ray->img_offset_begin=%lf, ray->begin_distance.y=%d, ray->base_angle = %lf, tan_val=%lf, z=%lf \n ", img_point.x, ray->wall_img->width, x, img_x_offset, ratio, ray->img_offset_begin, ray->begin_distance.y, ray->base_angle * 180 / M_PI, tan_val, z);
	if (img_point.x >= ray->wall_img->width)
		return (true);
	//printf("No.2 img_point.x=%d,ray->wall_img->width=%d, x=%d,img_x_offset=%d,ratio=%lf, ray->img_offset_begin=%lf \n ", img_point.x, ray->wall_img->width, x, img_x_offset, ratio, ray->img_offset_begin);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;
	double tmp_x = ((((x - img_x_offset) * ratio)  + ray->img_offset_begin) * ray->wall_img->width / WALL_LEN);// + ray->img_offset_begin;
	double tmp_angle = (img_point.x - ray->img_offset_begin / WALL_LEN * ray->wall_img->width ) / ray->wall_img->width * WALL_LEN * ray->last_angle / (ray->last_angle - ray->base_angle);
	tmp_angle = tmp_x * ((ray->last_angle - ray->base_angle) / (ray->wall_img->width - ray->img_offset_begin * ray->wall_img->width / WALL_LEN)) * (tmp_x -  ray->img_offset_begin * ray->wall_img->width / WALL_LEN) / ray->wall_img->width +  ray->base_angle;
	tan_val = (tan(tmp_angle));
	if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN)
		z = ray->begin_distance.y;
	else
		z = ray->begin_distance.x / tan(angle);

	double world_height = z * WALL_LEN / BASE_ZY;
	double offset_win = (z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height;
	ratio = ray->wall_img->height / world_height;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		if (y < offset_win)
		{
			win_img_addr[x] = 255 + 256 * 255;
			y++;
			continue;
		}
		img_point.y = y / WIN_HEIGHT * world_height - offset_win;
		//y = img_point.y * WIN_HEIGHT / world_height  + offset_win;
		img_point.y = (y - offset_win) * world_height / WIN_HEIGHT / 2;

		if (0 <= img_point.y && img_point.y < ray->wall_img->height && 0 <= img_point.x && img_point.x < ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
		{
			win_img_addr[x] = 65535 * 255;
			if (y == 5)
			{
				/*
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
					*/
			}
			//if (y == 100)
				//printf("blank x=%d, img_point.x=%d, img_point.y=%d\n", x, img_point.x, img_point.y);
		}
		else
		{
			win_img_addr[x] = 255;
		}
		y++;
	}
	return (false);
}

int	update_image_per_wall(t_cub3d *cub3d, t_ray *ray, int offset)
{
	t_cub3d_type	angle;
	int		end_image_flag;

	int	i;
	//j = 

	i = 0;
	while (i + offset < WIN_WIDTH)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		end_image_flag = update_image_per_x(cub3d, i + offset, offset, ray, angle);
		if (end_image_flag)
			break ;
		i++;
	}
	//printf("i=%d\n", i);
	return (i + offset);
}

int	update_image(t_cub3d *cub3d)
{
	//t_matrix	matrix;
	//t_xyz		src_xyz;
	//t_xyz		dst_xyz;
	int		i;
	//size_t		next_i;
	int		j;
	t_ray		ray;
	//t_point		map_point;
	//t_cub3d_type	z;
	t_cub3d_type	angle;
	//t_cub3d_type	pre_last_angle;

	//map_point.x = 0;
	i = 0;
	//next_i = 0;
	j = 0;


	cub3d->player->map_x = 2;
	cub3d->player->map_y = 4;
	cub3d->player->map.x = 2;
	cub3d->player->map.y = 4;
	cub3d->player->x = 20;
	cub3d->player->y = 0;
	cub3d->player->world_x = cub3d->player->map.x * WALL_LEN + cub3d->player->x;
	cub3d->player->world_y = cub3d->player->map.y * WALL_LEN + cub3d->player->y;
	cub3d->player->dir.degree = 0;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
	ft_memset(&ray, 0, sizeof(ray));
	
	//cub3d->rays[j].last_angle = (cub3d->player->dir.radian + cub3d->angles[0].radian) + 1;
	ray.last_angle = (cub3d->player->dir.radian + cub3d->angles[0].radian) + 1;
	//pre_last_angle = NAN;
	printf("\nstart\n");
	while (i < WIN_WIDTH)
	{
		angle = (cub3d->player->dir.radian + cub3d->angles[i].radian);
		if (angle > 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		//else if (angle < 0)
			//angle += 360 * M_PI / 180;
		fire_ray(cub3d, &ray, angle);
		//pre_last_angle = ray.last_angle;
		i = update_image_per_wall(cub3d, &ray, i);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image->img, 0, 0);
	return (true);
}
