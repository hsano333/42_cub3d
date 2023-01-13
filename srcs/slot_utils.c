/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:58:27 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 21:09:54 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slot_utils.h"

void	set_on_slot(t_cub3d *cub3d, t_ray *ray, t_map door_p)
{
	door_p.state = SLOT;
	cub3d->slot.shot_wall = ray->wall_dir;
	cub3d->slot.slot_flag = true;
	cub3d->slot.map_point = ray->map_point;
	//cub3d->slot.map_point.x = ray->map_point.x;
	//cub3d->slot.map_point.y = ray->map_point.y;
}

void	set_off_slot(t_cub3d *cub3d, t_ray *ray, t_map door_p)
{
	cub3d->slot.slot_flag = false;
	if (ray->wall_img == cub3d->walls->enemy)
	{
		door_p.state = SLOT_RESULT;
		cub3d->slot.result_flag = true;
		cub3d->slot.release_count = cub3d->frame_count;
	}
	else
		door_p.state = OTHER;
}
