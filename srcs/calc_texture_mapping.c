/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture_mapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:53:34 by hsano             #+#    #+#             */
/*   Updated: 2023/01/11 08:14:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc_texture_mapping.h"

//void	calc_texture_mapping(t_cub3d *cub3d)
//double		update_image_per_x(t_cub3d *cub3d, int x, t_ray *ray, t_cub3d_type angle, t_cub3d_type old_x)
void	calc_texture_mapping(t_cub3d *cub3d, int x, t_ray *ray, t_cub3d_type angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;
	t_cub3d_type z = 0;
	//nt_cub3d_type ratio = 0;
	t_cub3d_type	tmp_x;
	t_cub3d_type	tmp_y;
	t_cub3d_type	r;
	double		img_x_ratio;
	double		img_y_ratio;

	img_x_ratio = (double)ray->wall_img->width / WALL_LEN;
	img_y_ratio = (double)ray->wall_img->height / WALL_LEN;


	y = z;
	y = 0;
	if (ray->begin_distance.y == ray->last_distance.y)
	{
		tmp_x = (t_cub3d_type)fabs((double)ray->begin_distance.y * tan(angle));
		tmp_y = (t_cub3d_type)fabs((double)ray->begin_distance.y);
	}
	else if (ray->begin_distance.x == ray->last_distance.x)
	{
		tmp_x = (t_cub3d_type)fabs((double)ray->begin_distance.x);
		tmp_y = (t_cub3d_type)fabs((double)ray->begin_distance.x / tan(angle));
	}
	r = sqrt(pow(tmp_x, 2) + pow(tmp_y, 2));
	z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
	double cur_base_len = tan(angle - cub3d->player->dir.radian);
	double diff_len =  cur_base_len - ray->begin_base_len;
	double ratio_image =  diff_len / ray->max_len;
	img_point.x = (int)(((ratio_image)) * (ray->wall_img->width));
	if (ray->wall_dir == SOUTH_WALL)
		img_point.x = (int)((ray->begin_distance.x - ray->begin_distance.y * tan(angle)) * img_x_ratio);
	else if (ray->wall_dir == NORTH_WALL)
		img_point.x = (int)((-ray->begin_distance.x + ray->begin_distance.y * tan(angle - M_PI)) * img_x_ratio);
	else if (ray->wall_dir == EAST_WALL)
		img_point.x = (int)((-ray->begin_distance.y - (ray->begin_distance.x) * tan(angle - M_PI * 1 / 2)) * img_x_ratio);
	else if (ray->wall_dir == WEST_WALL)
		img_point.x = (int)((ray->begin_distance.y + (ray->begin_distance.x) * tan(angle - M_PI * 3 / 2)) * img_x_ratio);
	win_img_addr = NULL;
	img_addr = NULL;
	wall_flag = false;

	double world_height = z * WALL_LEN / BASE_ZY;
	double offset_win = ((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);
	//nnratio = ray->wall_img->height / world_height;
	wall_flag = false;

	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		img_point.y = (y - offset_win) * world_height / WIN_HEIGHT  * img_y_ratio;

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
}
