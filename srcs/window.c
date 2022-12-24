/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/24 08:45:31 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"
#include "ray.h"
#include "close.h"

int	update_image_per_x(t_cub3d *cub3d, int x, int img_x_offset, t_ray *ray, t_cub3d_type angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;
	t_cub3d_type offset = (ray->distance.x / tan(angle)) / 2 - WALL_LEN;
	t_cub3d_type z = 0;
	t_cub3d_type ratio = 0;
	t_cub3d_type tan_val;

	y = z;
	y = 0;

	tan_val = tan(angle); 
	if (ray->begin_distance.y == ray->last_distance.y || tan_val == NAN)
		z = ray->begin_distance.y;
	else
		z = ray->begin_distance.x / tan_val;
	//offset = z * WALL_LEN / WIN_WIDTH - WALL_LEN / 2;
	//offset = ray->begin_x;
	ratio = z / RATIO_Z;
	img_point.x = (int)(((x - img_x_offset) * ratio) * ray->wall_img->width / WALL_LEN) + ray->img_offset_begin / ratio;
	//printf("img_point.x=%d,ray->wall_img->width=%d\n ",img_point.x, ray->wall_img->width);
	if (img_point.x >= ray->wall_img->width)
		return (true);
	//return (0);
	//img_point.x = (int)((((((x - ray->begin_x) * (WALL_LEN - ray->img_offset_begin - ray->img_offset_last) / (ray->last_x - ray->begin_x)))) + (ray->img_offset_begin)) * ray->wall_img->width / WALL_LEN);
	//img_point.x = (int)((((((x - ray->begin_x) * (WALL_LEN - ray->img_offset_begin - ray->img_offset_last) / (ray->last_x - ray->begin_x)))) + (ray->img_offset_begin)) * ray->wall_img->width / WALL_LEN);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		if ((0 < angle && angle < 0.1 * M_PI / 180) || (179.9999 * M_PI / 180 < angle && angle < 180.0001 * M_PI / 180))
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.y / ray->wall_img->height);
		else if ((89.99999 * M_PI / 180 < angle && angle < 90.000001 * M_PI / 180) && (269.99999  * M_PI / 180 < angle && angle < 270.000001 * M_PI / 180))
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.x / ray->wall_img->height);
		else
			img_point.y = (int)nearbyintl(((double)y * WALL_LEN / WIN_HEIGHT) * ray->distance.x / tan(angle) / ray->wall_img->height);
		//double tmp = ((ray->distance.x / tan(angle)) / RATIO_Z);

		offset = z * WALL_LEN / WIN_HEIGHT - WALL_LEN / 2;
		ratio = z / RATIO_Z;
		img_point.y = (y * ratio - offset) * ray->wall_img->height / WALL_LEN;


		/*
		if (tan(angle) != NAN)
			img_point.y = (int)(y / (RATIO_Z / (ray->distance.x / tan(angle))) + offset);
		else
			img_point.y = (int)(y / (RATIO_Z / (ray->distance.x )) + offset);

		if (ray->begin_distance.y == ray->last_distance.y)
		{
			img_point.y = (int)(y  * ray->begin_distance.y / RATIO_Z );
		}
		else
			img_point.y = (int)(y  * ray->begin_distance.y / (RATIO_Z * tan(angle) ));
		*/
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
			if (y == 5)
			{
				if (!(0 <= img_point.x && img_point.x < ray->wall_img->width))
					printf("invalid x: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d,ray->begin_x=%d, ray->last_x=%d , z=%lf, ratio=%lf, ig_x_offset=%d, offset=%lf  \n", x, img_point.x, y, img_point.y, ray->begin_x, ray->last_x, z, ratio, img_x_offset, ray->img_offset_begin / ratio);
				if (!(0 <= img_point.y && img_point.y < ray->wall_img->height))
					printf("invalid y: x=%d, test img_point.x=%d,  y=%d, test img_point.y=%d \n", x, img_point.x, y, img_point.y);
			}
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
		i++;
		if (end_image_flag)
			break ;
	}
	return (i + offset);

	//printf("cub3d->player->dir=%d, angle[%zu]=%f, angle=%f\n", cub3d->player->dir,i, cub3d->angles[i], angle);
	//i = cub3d->rays[i].next_i;
	//printf("i=%d\n",i);
	//if (i == cub3d->rays[j].next_i || i == 0)
	//{
		////z = tan(cub3d->rays[j].begin_angle);
		//j = i;
	//}
	return (i);
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
	//t_cub3d_type	z;
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
	cub3d->player->x = 300;
	cub3d->player->y = 250;
	cub3d->player->dir.degree = 0;
	cub3d->player->dir.radian = 0 * M_PI / 180;
	
	//map_point = cub3d->rays[j].map_point;
	//printf("map_point=%d\n", map_point.x);
	cub3d->rays[j].last_angle = (cub3d->player->dir.radian + cub3d->angles[0].radian) + 1;
	//printf("No.0 angle\n");
	cub3d->rays[0].last_x = -1;
	int tmp = 0;
	while (i < WIN_WIDTH)
	{
		//if (angle > cub3d->rays[j].begin_angle)
			//angle -= 360 * M_PI / 180;
		//if (is_next_wall(&(cub3d->rays[j]), angle))
		//if (i >= cub3d->rays[j].last_x)
		//{
		angle = (cub3d->player->dir.radian + cub3d->angles[i].radian);
		if (angle > 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		//cub3d->rays[j].next_i = i;
		//j = i;
		//cub3d->rays[j].cur_angle = angle;
		printf("fire renew i=%d, j=%d, angle=n%lf\n", i, j, angle * 180 / M_PI);
		printf("No.1 angle =%lf,cub3d->rays[j].last_angle=%lf i=%d, j=%d\n", angle,cub3d->rays[j].last_angle, i, j);
		tmp = fire_ray(cub3d, &(cub3d->rays[j]), i, angle, tmp);
		//i = update_image_per_wall();
		i = update_image_per_wall(cub3d, &cub3d->rays[j], i);
		printf("No.2 angle =%lf,cub3d->rays[j].last_angle=%lf i=%d, j=%d\n", angle,cub3d->rays[j].last_angle, i, j);
		j++;
			//printf("No.2 angle =%lf,cub3d->rays[j].last_angle=%lf i=%ld, j=%ld\n", angle,cub3d->rays[j].last_angle, i, j);
		//}
		//z = tan(cub3d->rays[j].begin_angle);
		//printf("cub3d->player->dir=%d, angle[%zu]=%f, angle=%f\n", cub3d->player->dir,i, cub3d->angles[i], angle);
		//update_image_per_x(cub3d, i, z, &cub3d->rays[j], angle);
		//i++;
	}
	//cub3d->rays[j].next_i = i;

	//i = 0;
	//j = 0;
	//z = tan(cub3d->rays[j].begin_angle);
	/*
	while (i < WIN_WIDTH)
	{
		///i = update_image_per_wall(cub3d, i, j, &cub3d->rays[j], angle);
		//j = cub3d->rays[j].next_i;
		j++;
	}
	*/

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
