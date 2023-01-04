/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2023/01/04 11:39:10 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "projective_trans.h"
#include "ray.h"
#include "close.h"
#include "libft_mem.h"
#include <float.h>

//double	update_image_per_x(t_cub3d *cub3d, int x, int img_x_offset, t_ray *ray, t_cub3d_type angle, t_cub3d_type old_x)
double		update_image_per_x(t_cub3d *cub3d, int x, t_ray *ray, t_cub3d_type angle, t_cub3d_type old_x)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;
	t_cub3d_type z = 0;
	t_cub3d_type ratio = 0;
	t_cub3d_type	tmp_x;
	t_cub3d_type	tmp_y;
	t_cub3d_type	r;

	y = z;
	y = 0;
	if (ray->begin_distance.y == ray->last_distance.y)
	{
		tmp_x = fabs(ray->begin_distance.y * tan(angle));
		tmp_y = fabs(ray->begin_distance.y);
	}
	else if (ray->begin_distance.x == ray->last_distance.x)
	{
		tmp_x = fabs(ray->begin_distance.x);
		tmp_y = fabs(ray->begin_distance.x / tan(angle));
	}
	r = sqrt(pow(tmp_x, 2) + pow(tmp_y, 2));
	//printf("\ncub3d->angles[i].degree=%lf\n", cub3d->angles[0].degree);
	//double begin_base_len = tan(ray->begin_angle - cub3d->player->dir.radian);
	double begin_base_len = tan(ray->start_angle - cub3d->player->dir.radian);
	double last_base_len = tan(ray->last_angle - cub3d->player->dir.radian);
	double cur_base_len = tan(angle - cub3d->player->dir.radian);
	/*
	if (ray->is_front_wall)
	{
		begin_base_len = tan(ray->begin_angle - cub3d->player->dir.radian);
		last_base_len = tan(ray->last_angle - cub3d->player->dir.radian);
		cur_base_len = tan(angle - cub3d->player->dir.radian);
	}
	else
	{
		begin_base_len = tan(ray->begin_angle - cub3d->player->dir.radian - M_PI / 2);
		last_base_len = tan(ray->last_angle - cub3d->player->dir.radian - M_PI / 2);
		cur_base_len = tan(angle - cub3d->player->dir.radian - M_PI / 2);
	}
	*/

	double max_len =  last_base_len - begin_base_len;
	double diff_len =  cur_base_len - begin_base_len ;
	double ratio_image =  diff_len / max_len;
	//double tmp_angle =angle - cub3d->player->dir.radian - M_PI / 2; 
	img_point.x = (int)(((ratio_image)) * ray->wall_img->width);
	//printf(" img_point.x=%d, ray->is_front_wall=%d, ratio_image=%lf, tmp_angle=%lf\n", img_point.x, ray->is_front_wall, ratio_image, tmp_angle*180 / M_PI);
	//printf("x=%d, z=%lf,diff_len=%lf,max_len=%lf,last_base_len=%lf,begin_base_len=%lf,cur_base_len=%lf  \n",x, z, diff_len, max_len,last_base_len,begin_base_len,cur_base_len);
	//printf("angle=%lf,ray->begin_angle=%lf,ray->last_angle=%lf,cub3d->player->dir.radian=%lf \n", angle * 180 / M_PI,ray->begin_angle*180/M_PI,ray->last_angle*180/M_PI, cub3d->player->dir.radian*180/M_PI);
	//printf("r=%lf,tmp_angle=%lf, angle=%lf,player_dir=%lf, cos=%lf, sin=%lf,tan=%lf\n",r,tmp_angle * 180 / M_PI, angle * 180 / M_PI,cub3d->player->dir.radian * 180 / M_PI, cos(tmp_angle), sin(tmp_angle), tan(tmp_angle));
	old_x += ratio;


	//0 180 OK
	z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));

	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;

	double world_height = z * WALL_LEN / BASE_ZY;
	double offset_win = ((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);
	ratio = ray->wall_img->height / world_height;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		img_point.y = (y - offset_win) * world_height / WIN_HEIGHT / 2;

		if (0 <= img_point.y && img_point.y <= ray->wall_img->height && 0 <= img_point.x && img_point.x <= ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
		{
			win_img_addr[x] = 65535 * 255;
		}
		else
		{
			win_img_addr[x] = 255;
		}
		y++;
	}
	return (old_x);
}

static int	calc_wall_pixel(t_cub3d *cub3d, t_ray *ray, int offset)
{
	int	i;
	t_cub3d_type	angle;

	i = 0;
	while (i + offset < WIN_WIDTH)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		i++;
		if (is_next_wall(ray, angle))
			break ;
	}
	return (i);
}

int	update_image_per_wall(t_cub3d *cub3d, t_ray *ray, int offset)
{
	t_cub3d_type	angle;
	t_cub3d_type	cur_x;
	int	i;

	i = 0;
	cur_x = 0;
	ray->wall_pixel = calc_wall_pixel(cub3d, ray, offset);
	//printf("len=%d\n", ray->wall_pixel);
	while (i < ray->wall_pixel)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		cur_x = update_image_per_x(cub3d, i + offset, ray, angle, cur_x);
		if (is_next_wall(ray, angle))
			break ;
		i++;
	}
	return (i + offset);
}

int	update_image(t_cub3d *cub3d)
{
	int		i;
	int		j;
	t_ray		ray;
	t_cub3d_type	angle;

	i = 0;
	j = 0;


	//cub3d->player->map_x = 5;
	//cub3d->player->map_y = 1;
	cub3d->player->map.x = 3;
	cub3d->player->map.y = 3;
	//cub3d->player->x = 200;
	//cub3d->player->y = 200;
	cub3d->player->mass.x = 200;
	cub3d->player->mass.y = 200;
	cub3d->player->world_x = cub3d->player->map.x * WALL_LEN + cub3d->player->mass.x;
	cub3d->player->world_y = cub3d->player->map.y * WALL_LEN + cub3d->player->mass.y;
	//cub3d->player->dir.degree = 0;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
	ft_memset(&ray, 0, sizeof(ray));
	
	ray.last_angle = (cub3d->player->dir.radian + cub3d->angles[0].radian) + 1;
	ray.x = 0;
	//printf("\nstart,player point.x=%d, y=%d\n", cub3d->player->map.x, cub3d->player->map.y);
	while (i < WIN_WIDTH)
	{
		angle = (cub3d->player->dir.radian + cub3d->angles[i].radian);
		if (angle >= 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		else if (angle < 0)
			angle += 360 * M_PI / 180;
		fire_ray(cub3d, &ray, angle);
		i = update_image_per_wall(cub3d, &ray, i);
		j++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image->img, 0, 0);
	return (true);
}
