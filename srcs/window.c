/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2023/01/12 17:09:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "affine.h"
#include "ray.h"
#include "close.h"
#include "libft_mem.h"
#include <float.h>
#include "calc_texture_mapping.h"
#include "door.h"
#include "libft_mem.h"
#include "slot.h"

static	void	clear_state(t_cub3d *cub3d)
{
	t_point	wall;

	wall = cub3d->slot.map_point;
	cub3d->door_change_flag = false;
	cub3d->player->shot.x = -1;
	cub3d->player->shot.y = -1;
	count_frame(cub3d);

	if (cub3d->slot.result_flag)
		printf("result: slot count=%d,now=%d\n ", cub3d->slot.release_count, cub3d->frame_count);


	if (cub3d->slot.result_flag && cub3d->slot.release_count == cub3d->frame_count)
	{
		cub3d->map[wall.y][wall.x].state = OTHER;
		cub3d->slot.result_flag = false;
	}
}

static int	calc_wall_pixel(t_cub3d *cub3d, t_ray *ray, int offset)
{
	int		i;
	double	angle;

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
	double	angle;
	int		i;

	i = 0;
	ray->wall_pixel = calc_wall_pixel(cub3d, ray, offset);
	ray->shot_flag = is_raise_shot_flag(cub3d, ray, i + offset, i + offset + ray->wall_pixel);
	while (i < ray->wall_pixel)
	{
		angle = cub3d->player->dir.radian + cub3d->angles[i + offset].radian;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
		calc_texture_mapping(cub3d, i + offset, ray, angle);
		if (is_next_wall(cub3d, ray, angle))
			break ;
		i++;
	}
	ray->shot_flag = false;
	return (i + offset);
}

int	update_image(t_cub3d *cub3d)
{
	int		i;
	t_ray	ray;
	double	angle;

	i = 0;
	cub3d->player->world_x = cub3d->player->map.x * WALL_LEN \
													+ cub3d->player->mass.x;
	cub3d->player->world_y = cub3d->player->map.y * WALL_LEN \
													+ cub3d->player->mass.y;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
	ft_memset(&ray, 0, sizeof(t_ray));
	while (i < WIN_WIDTH)
	{
		angle = (cub3d->player->dir.radian + cub3d->angles[i].radian);
		if (angle >= 360 * M_PI / 180)
			angle -= 360 * M_PI / 180;
		else if (angle < 0)
			angle += 360 * M_PI / 180;
		ray.tmp_offset = i;
		ray.start_angle = angle;
		fire_ray(cub3d, &ray, angle);
		i = update_image_per_wall(cub3d, &ray, i);
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->window \
								, cub3d->image->img, 0, 0);
	clear_state(cub3d);
	return (true);
}
