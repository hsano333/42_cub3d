/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture_mapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:53:34 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 07:22:24 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc_texture_mapping.h"
#include "slot.h"

int	calc_z(t_cub3d *cub3d, t_ray *ray, double angle)
{
	double	tmp_x;
	double	tmp_y;
	double	r;
	double	z;

	if (ray->begin_distance.y == ray->last_distance.y)
	{
		tmp_x = (double)fabs((double)ray->begin_distance.y * tan(angle));
		tmp_y = (double)fabs((double)ray->begin_distance.y);
	}
	else if (ray->begin_distance.x == ray->last_distance.x)
	{
		tmp_x = (double)fabs((double)ray->begin_distance.x);
		tmp_y = (double)fabs((double)ray->begin_distance.x / tan(angle));
	}
	r = sqrt(pow(tmp_x, 2) + pow(tmp_y, 2));
	z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
	return (z);

}

int	calc_x(t_ray *ray, double angle)
{
	//double	cur_base_len;
	//double	diff_len;
	//double	ratio_image;
	double	img_x_ratio;
	double	image_x;

	img_x_ratio = (double)ray->wall_img->width / WALL_LEN;
	//cur_base_len = tan(angle - cub3d->player->dir.radian);
	//diff_len =  cur_base_len - ray->begin_base_len;
	//ratio_image =  diff_len / ray->max_len;
	if (ray->wall_dir == SOUTH_WALL)
		image_x = (int)((ray->begin_distance.x - ray->begin_distance.y * tan(angle)) * img_x_ratio);
	else if (ray->wall_dir == NORTH_WALL)
		image_x = (int)((-ray->begin_distance.x + ray->begin_distance.y * tan(angle - M_PI)) * img_x_ratio);
	else if (ray->wall_dir == EAST_WALL)
		image_x = (int)((-ray->begin_distance.y - (ray->begin_distance.x) * tan(angle - M_PI * 1 / 2)) * img_x_ratio);
	else if (ray->wall_dir == WEST_WALL)
		image_x = (int)((ray->begin_distance.y + (ray->begin_distance.x) * tan(angle - M_PI * 3 / 2)) * img_x_ratio);
	return (image_x);
}
int	calc_y(t_ray *ray, double angle)
{
	//double	cur_base_len;
	//double	diff_len;
	//double	ratio_image;
	double	img_x_ratio;
	double	image_x;

	img_x_ratio = (double)ray->wall_img->width / WALL_LEN;
	//cur_base_len = tan(angle - cub3d->player->dir.radian);
	//diff_len =  cur_base_len - ray->begin_base_len;
	//ratio_image =  diff_len / ray->max_len;
	if (ray->wall_dir == SOUTH_WALL)
		image_x = (int)((ray->begin_distance.x - ray->begin_distance.y * tan(angle)) * img_x_ratio);
	else if (ray->wall_dir == NORTH_WALL)
		image_x = (int)((-ray->begin_distance.x + ray->begin_distance.y * tan(angle - M_PI)) * img_x_ratio);
	else if (ray->wall_dir == EAST_WALL)
		image_x = (int)((-ray->begin_distance.y - (ray->begin_distance.x) * tan(angle - M_PI * 1 / 2)) * img_x_ratio);
	else if (ray->wall_dir == WEST_WALL)
		image_x = (int)((ray->begin_distance.y + (ray->begin_distance.x) * tan(angle - M_PI * 3 / 2)) * img_x_ratio);
	return (image_x);
}

/*
void	copy_to_addr(t_cub3d *cub3d, t_ray *ray, t_point img_point, int *win_img_add)
{
	//int	y;
	int	*win_img_addr;
	//int	wall_flag;
	int	*img_addr;
	double world_height;
	double offset_win;
	double		img_y_ratio;

	//y = 0;
	//img_y_ratio = (double)ray->wall_img->height / WALL_LEN;
	//wall_flag = false;
	//world_height = z * WALL_LEN / BASE_ZY;
	//offset_win = ((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);
	//while (y < WIN_HEIGHT)
	{
		//win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		//img_point.y = (y - offset_win) * world_height / WIN_HEIGHT  * img_y_ratio;

		//manage_slot_flag(cub3d, ray);
		if (0 <= img_point.y && img_point.y <= ray->wall_img->height && 0 <= img_point.x && img_point.x <= ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			*wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (*wall_flag)
			win_img_addr[x] = cub3d->floor.color;
		else
			win_img_addr[x] = cub3d->ceiling.color;
	}
}
*/

void	calc_texture_mapping(t_cub3d *cub3d, int x, t_ray *ray, double angle)
{
	t_point	img_point;
	int	*win_img_addr;
	int	y;
	double z;
	double		img_y_ratio;
	int	wall_flag;
	double world_height;
	double offset_win;
	int	*img_addr;

	z = calc_z(cub3d, ray, angle);
	img_point.x = calc_x(ray, angle);
	img_y_ratio = (double)ray->wall_img->height / WALL_LEN;
	wall_flag = false;
	world_height = z * WALL_LEN / BASE_ZY;
	offset_win = ((z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) * WIN_HEIGHT / world_height);

	y = 0;
	while (y < WIN_HEIGHT)
	{
		win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
		img_point.y = (y - offset_win) * world_height / WIN_HEIGHT  * img_y_ratio;
		manage_slot_flag(cub3d, ray, y);
		if (0 <= img_point.y && img_point.y <= ray->wall_img->height && 0 <= img_point.x && img_point.x <= ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
			win_img_addr[x] = cub3d->floor.color;
		else
			win_img_addr[x] = cub3d->ceiling.color;
		y++;
	}
}

/*
void	calc_texture_mapping(t_cub3d *cub3d, int x, t_ray *ray, double angle)
{
	int	*win_img_addr;
	int	*img_addr;
	int	y;
	int	wall_flag;
	t_point	img_point;
	double z = 0;
	//ndouble ratio = 0;
	double	tmp_x;
	double	tmp_y;
	double	r;
	double		img_x_ratio;
	double		img_y_ratio;

	img_x_ratio = (double)ray->wall_img->width / WALL_LEN;
	img_y_ratio = (double)ray->wall_img->height / WALL_LEN;


	y = z;
	y = 0;
	if (ray->begin_distance.y == ray->last_distance.y)
	{
		tmp_x = (double)fabs((double)ray->begin_distance.y * tan(angle));
		tmp_y = (double)fabs((double)ray->begin_distance.y);
	}
	else if (ray->begin_distance.x == ray->last_distance.x)
	{
		tmp_x = (double)fabs((double)ray->begin_distance.x);
		tmp_y = (double)fabs((double)ray->begin_distance.x / tan(angle));
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

		if (ray->shot_flag && cub3d->player->shot.y == y && cub3d->map[ray->map_point.y][ray->map_point.x].obj != DOOR)
		{
			if (cub3d->slot.slot_flag)
			{
				cub3d->slot.slot_flag = false;
				if (ray->wall_img == cub3d->walls->enemy)
				{

					printf("shot result No.1, y=%d,x=%d \n", ray->map_point.y, ray->map_point.x);
					cub3d->map[ray->map_point.y][ray->map_point.x].state = SLOT_RESULT;
					cub3d->slot.result_flag = true;
					cub3d->slot.release_count = cub3d->frame_count;
				}
				else
				{
					printf("shot result No.2, y=%d,x=%d \n", ray->map_point.y, ray->map_point.x);
					cub3d->map[ray->map_point.y][ray->map_point.x].state = OTHER;
				}
			}
			else
			{
				printf("shot result No.0, y=%d,x=%d \n", ray->map_point.y, ray->map_point.x);
				//printf("ray->map_point.y=%d, x=%d\n", ray->map_point.y, ray->map_point.x);
				cub3d->map[ray->map_point.y][ray->map_point.x].state = SLOT;
				cub3d->slot.shot_wall = ray->wall_dir;
				cub3d->slot.slot_flag = true;
				cub3d->slot.map_point.x = ray->map_point.x;
				cub3d->slot.map_point.y = ray->map_point.y;

			}
			
				ray->shot_flag = false;
		}
		if (0 <= img_point.y && img_point.y <= ray->wall_img->height && 0 <= img_point.x && img_point.x <= ray->wall_img->width)
		{
			img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
			wall_flag = true;
			win_img_addr[x] = img_addr[img_point.x];
		}
		else if (wall_flag)
		{
			win_img_addr[x] = cub3d->floor.color;
		}
		else
		{
			win_img_addr[x] = cub3d->ceiling.color;
		}
		y++;
	}
}
*/
