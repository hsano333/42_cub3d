/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/31 16:56:53 by hsano            ###   ########.fr       */
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
	t_cub3d_type	tmp_x;
	t_cub3d_type	tmp_y;
	t_cub3d_type	r;
	//t_cub3d_type far_height;

	y = z;
	y = 0;

	if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN)
	{
		tmp_x = ray->begin_distance.y * tan(angle);
		tmp_y = ray->begin_distance.y;
	}
	else if (ray->begin_distance.x == ray->last_distance.x)
	{
		tmp_x = fabs(ray->begin_distance.x);
		tmp_y = ray->begin_distance.x * tan(M_PI / 2 - angle);
		//tmp_y = fabs(ray->begin_distance.x * tan(angle - cub3d->player->dir.radian));
	}
	r = sqrt(pow(tmp_x, 2) + pow(tmp_y, 2));
	//else
		//tmp_x = 

	//tan_val = (tan(tmp_angle));
	tan_val = (tan(ray->base_angle - cub3d->player->dir.radian));
	//double tmp_z = math.sqrt(begin_distance.x * begin_distance.x + begin_distance.y * begin_distance.y);
	//if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN || tan(ray->base_angle) == NAN)
	if (ray->begin_distance.y == ray->last_distance.y)
		z = fabs(ray->begin_distance.y);
	else if (ray->begin_distance.x == ray->last_distance.x)
		z = fabs(ray->last_distance.x);
	else
		//z = fabs(ray->last_distance.x);
		z = fabs(ray->last_distance.y / tan_val);
	//z = 
	if (ray->begin_distance.y == ray->last_distance.y)
		z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(ray->begin_distance.y);
	else if (ray->begin_distance.x == ray->last_distance.x)
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		z = fabs(r * cos(cub3d->player->dir.radian - angle));
	ratio = z / BASE_ZX;
	img_point.x = (int)((((x - img_x_offset) * ratio) + ray->img_offset_begin) * ray->wall_img->width / WALL_LEN);


	//test
	///*  OK
	tan_val = (tan(ray->base_angle));
	if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN || tan(ray->base_angle) == NAN)
		z = fabs(ray->begin_distance.y);
	else
		z = fabs(ray->last_distance.y / tan_val);
	ratio = z / BASE_ZX;
	img_point.x = (int)((((x - img_x_offset) * ratio) + ray->img_offset_begin) * ray->wall_img->width / WALL_LEN);
	//*/



	if (img_point.x >= ray->wall_img->width - 20 || x - img_x_offset < 20)
	{
	printf("x=%d,img_point.x=%d,tmp_x=%lf, tmp_y=%lf, r=%lf, z=%lf, angle=%lf, player_dir=%lf\n",x,img_point.x, tmp_x, tmp_y, r, z, angle * 180 / M_PI, cub3d->player->dir.radian * 180 / M_PI);
	}
	//if (img_point.x >= ray->wall_img->width - 20 || x - img_x_offset < 20)
		//printf("No.1 img_point.x=%d,ray->wall_img->width=%d, x=%d,img_x_offset=%d,ratio=%lf, ray->img_offset_begin=%lf, ray->begin_distance.y=%d, ray->base_angle = %lf, tan_val=%lf, z=%lf \n ", img_point.x, ray->wall_img->width, x, img_x_offset, ratio, ray->img_offset_begin, ray->begin_distance.y, ray->base_angle * 180 / M_PI, tan_val, z);
	if (img_point.x >= ray->wall_img->width)
		return (true);


	if (ray->begin_distance.y == ray->last_distance.y)
		z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(r * cos(cub3d->player->dir.radian));
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(ray->begin_distance.y);
	else if (ray->begin_distance.x == ray->last_distance.x)
		z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(r * cos(angle + cub3d->player->dir.radian));
		//z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
		//z = fabs(r * cos(angle - cub3d->player->dir.radian));
		//z = fabs(r * cos(M_PI / 2 - (angle - cub3d->player->dir.radian)));
		//z = fabs(r * sin(angle - cub3d->player->dir.radian));
		//z = fabs(ray->begin_distance.x);
	else
	{
		z = r;
		//z = fabs(ray->begin_distance.x * sin(angle));
	}
		z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));


	//printf("No.2 img_point.x=%d,ray->wall_img->width=%d, x=%d,img_x_offset=%d,ratio=%lf, ray->img_offset_begin=%lf \n ", img_point.x, ray->wall_img->width, x, img_x_offset, ratio, ray->img_offset_begin);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;
	//double tmp_x = ((((x - img_x_offset) * ratio)  + ray->img_offset_begin) * ray->wall_img->width / WALL_LEN);// + ray->img_offset_begin;
	//double tmp_angle = (img_point.x - ray->img_offset_begin / WALL_LEN * ray->wall_img->width ) / ray->wall_img->width * WALL_LEN * ray->last_angle / (ray->last_angle - ray->base_angle);
	//tmp_angle = tmp_x * ((ray->last_angle - ray->base_angle) / (ray->wall_img->width - ray->img_offset_begin * ray->wall_img->width / WALL_LEN)) * (tmp_x -  ray->img_offset_begin * ray->wall_img->width / WALL_LEN) / ray->wall_img->width +  ray->base_angle;
	//double r = 0;
		//z = fabs(ray->begin_distance.x / tan(angle));

	double world_height = z * WALL_LEN / BASE_ZY;
	//double tmp1 = z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2;
	//double offset_win =fabs((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);
	double offset_win = ((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);
	ratio = ray->wall_img->height / world_height;
	wall_flag = false;
	printf("y: x=%d,img_x_offset=%d, z=%lf,  world_height=%lf, offset_win=%lf, ratio=%lf, tmp1= \n",x, img_x_offset, z,world_height, offset_win, ratio);
	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		/*
		if (y < offset_win)
		{
			win_img_addr[x] = 255 + 256 * 255;
			y++;
			continue;
		}
		*/
		//img_point.y = y / WIN_HEIGHT * world_height - offset_win;
		//y = img_point.y * WIN_HEIGHT / world_height  + offset_win;
		//if (ratio <= 1)
		img_point.y = (y - offset_win) * world_height / WIN_HEIGHT / 2;
		//else
			//img_point.y = y;

		if (0 <= img_point.y && img_point.y < ray->wall_img->height && 0 <= img_point.x && img_point.x < ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
			/*
			if (y <= 5 && x == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("valid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("valid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
			*/
		}
		else if (wall_flag)
		{
			win_img_addr[x] = 65535 * 255;
			/*
			if (y == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
			*/
			//if (y == 100)
				//printf("blank x=%d, img_point.x=%d, img_point.y=%d\n", x, img_point.x, img_point.y);
		}
		else
		{
			/*
			if (y == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
			*/
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
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		//printf("angle=%lf,i=%d, offset=%d,player=%lf\n  ", angle * 180/M_PI, i, offset, cub3d->player->dir.radian * 180 / M_PI);
		end_image_flag = update_image_per_x(cub3d, i + offset, offset, ray, angle);
		if (end_image_flag)
			break ;
		i++;
	}
	printf("end i=%d, offset=%d, angle=%lf\n", i,offset, angle * 180 / M_PI);
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


	cub3d->player->map_x = 3;
	cub3d->player->map_y = 3;
	cub3d->player->map.x = 3;
	cub3d->player->map.y = 3;
	cub3d->player->x = 200;
	cub3d->player->y = 200;
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
		else if (angle < 0)
			angle += 360 * M_PI / 180;
		fire_ray(cub3d, &ray, angle);
		//pre_last_angle = ray.last_angle;
		i = update_image_per_wall(cub3d, &ray, i);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image->img, 0, 0);
//	error_and_end_game(NULL, "cub3D:end\n");
	return (true);
}
