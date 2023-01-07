/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 08:52:36 by hsano            ###   ########.fr       */
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
	z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
	double cur_base_len = tan(angle - cub3d->player->dir.radian);
	double diff_len =  cur_base_len - ray->begin_base_len;
	double ratio_image =  diff_len / ray->max_len;
	img_point.x = (int)(((ratio_image)) * (ray->wall_img->width));
	if (ray->is_adjacent_wall)
	{

		if (ray->wall_dir == NORTH_WALL)
			img_point.x = (int)(cub3d->player->mass.x - cub3d->player->mass.y * tan(angle) ) / 2;
		else if (ray->wall_dir == SOUTH_WALL)
			img_point.x = (int)(cub3d->player->mass.x - cub3d->player->mass.y * tan(angle - M_PI)) / 2;
		else if (ray->wall_dir == EAST_WALL)
			img_point.x = (int)(cub3d->player->mass.x - cub3d->player->mass.y * tan(angle - M_PI * 3 / 2)) / 2;
		else if (ray->wall_dir == WEST_WALL)
			img_point.x = (int)(cub3d->player->mass.x - cub3d->player->mass.y * tan(angle - M_PI / 2)) / 2;
	}
	old_x += ratio;

	//0 180 OK

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
	int		i;
	t_cub3d_type	angle;

	i = 0;
	while (i + offset < WIN_WIDTH)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		i++;
		if (is_next_wall(cub3d, ray, angle))
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
	while (i < ray->wall_pixel)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		cur_x = update_image_per_x(cub3d, i + offset, ray, angle, cur_x);
		if (is_next_wall(cub3d, ray, angle))
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


	/*
	cub3d->player->map.x = 3;
	cub3d->player->map.y = 3;
	cub3d->player->mass.x = 200;
	cub3d->player->mass.y = 200;
	*/
	cub3d->player->world_x = cub3d->player->map.x * WALL_LEN + cub3d->player->mass.x;
	cub3d->player->world_y = cub3d->player->map.y * WALL_LEN + cub3d->player->mass.y;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
	ft_memset(&ray, 0, sizeof(ray));
	
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
