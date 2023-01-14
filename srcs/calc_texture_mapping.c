/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture_mapping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:53:34 by hsano             #+#    #+#             */
/*   Updated: 2023/01/14 16:18:33 by hsano            ###   ########.fr       */
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
	else
	{
		tmp_x = 0;
		tmp_y = 0;
	}
	r = sqrt(pow(tmp_x, 2) + pow(tmp_y, 2));
	z = fabs(r * sin(angle - cub3d->player->dir.radian - M_PI / 2));
	return (z);
}

int	calc_x(t_ray *ray, double angle)
{
	int		image_x;
	double	img_x_ratio;
	t_point	dist;

	dist = ray->begin_distance;
	img_x_ratio = (double)ray->wall_img->width / WALL_LEN;
	image_x = 0;
	if (ray->wall_dir == SOUTH_WALL)
		image_x = ((dist.x - dist.y * tan(angle)) * img_x_ratio);
	else if (ray->wall_dir == NORTH_WALL)
		image_x = ((-dist.x + dist.y * tan(angle - M_PI)) * img_x_ratio);
	else if (ray->wall_dir == EAST_WALL)
		image_x = ((-dist.y - dist.x * tan(angle - M_PI * 0.5)) * img_x_ratio);
	else if (ray->wall_dir == WEST_WALL)
		image_x = ((dist.y + dist.x * tan(angle - M_PI * 1.5)) * img_x_ratio);
	return (image_x);
}

int	copy_to_addr(t_cub3d *cub3d, t_point img_point \
									, t_point win_point, int wall_flag)
{
	int		*win_img_addr;
	int		*img_addr;
	int		x;
	int		y;
	t_ray	*ray;

	x = win_point.x;
	y = win_point.y;
	ray = cub3d->ray;
	win_img_addr = cub3d->image->addr + (cub3d->image->sl * y);
	if ((0 <= img_point.y && img_point.y <= ray->wall_img->height) \
			&& 0 <= img_point.x && img_point.x <= ray->wall_img->width)
	{
		img_addr = ray->wall_img->addr + (ray->wall_img->sl * img_point.y);
		wall_flag = true;
		win_img_addr[x] = img_addr[img_point.x];
	}
	else if (wall_flag)
		win_img_addr[x] = cub3d->floor.color;
	else
		win_img_addr[x] = cub3d->ceiling.color;
	return (wall_flag);
}

void	copy_to_addr_base(t_cub3d *cub3d, t_point img_point \
									, t_point win_point, double z)
{
	int		wall_flag;
	int		y;
	double	world_height;
	double	offset_win;
	double	img_y_ratio;

	y = 0;
	img_y_ratio = (double)cub3d->ray->wall_img->height / WALL_LEN;
	world_height = z * WALL_LEN / BASE_ZY;
	offset_win = (z / BASE_ZY * WALL_LEN / 2 - WALL_LEN / 2) \
									* WIN_HEIGHT / world_height;
	wall_flag = false;
	while (y < WIN_HEIGHT)
	{
		win_point.y = y;
		if (fabs(offset_win) == INFINITY)
			img_point.y = cub3d->ray->wall_img->height - 1;
		else
			img_point.y = (y - offset_win) \
					* world_height / WIN_HEIGHT * img_y_ratio;
		if (cub3d->ray->shot_flag)
			manage_slot_flag(cub3d, cub3d->ray, y);
		wall_flag = copy_to_addr(cub3d, img_point, win_point, wall_flag);
		y++;
	}
}

void	calc_texture_mapping(t_cub3d *cub3d, int x, t_ray *ray, double angle)
{
	t_point	img_point;
	t_point	win_point;
	double	z;

	img_point.x = calc_x(ray, angle);
	if (img_point.x >= ray->wall_img->width)
		img_point.x = ray->wall_img->width - 1;
	z = calc_z(cub3d, ray, angle);
	cub3d->ray = ray;
	win_point.x = x;
	copy_to_addr_base(cub3d, img_point, win_point, z);
}
