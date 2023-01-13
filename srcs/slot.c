/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:14:27 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 11:43:21 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slot.h"
#include "door.h"

int	is_raise_shot_flag(t_cub3d *cub3d, t_ray *ray, int start, int end)
{
	t_point	cur;
	t_point	old;
	int	is_same_wall;
	int	shot_x;

	shot_x = cub3d->player->shot.x;
	if (cub3d->slot.result_flag)
		return (false);
	cur = ray->map_point;
	old = cub3d->slot.map_point;
	is_same_wall = cur.x == old.x && cub3d->slot.shot_wall == ray->wall_dir;
	if (cub3d->slot.slot_flag == false || is_same_wall)
	{
		if (start <= shot_x && shot_x <= end)
			return (true);
	}
	return (false);
}

void	rotate_slot(t_cub3d *cub3d, t_ray *ray)
{
	if (cub3d->frame_count <= 10)
		ray->wall_img = cub3d->walls->north;
	else if (cub3d->frame_count <= 20)
		ray->wall_img = cub3d->walls->south;
	else if (cub3d->frame_count <= 30)
		ray->wall_img = cub3d->walls->west;
	else if (cub3d->frame_count <= 40)
		ray->wall_img = cub3d->walls->east;
	else if (cub3d->frame_count <= 50)
		ray->wall_img = cub3d->walls->door;
	else
		ray->wall_img = cub3d->walls->enemy;
}

void	change_image(t_cub3d *cub3d, t_ray *ray, t_point next)
{
	t_door_state	wall_state;
	t_wall_dir	wall_dir;

	wall_state = cub3d->map[next.y][next.x].state;
	wall_dir = cub3d->slot.shot_wall;
	if (ray->is_door)
		ray->wall_img = cub3d->walls->door;
	ray->is_door = false;
	if (cub3d->map[next.y][next.x].obj >= DOOR)
	{
		open_and_close_door(cub3d, next);
		ray->wall_img = cub3d->walls->door;
	}
	if (wall_state == SLOT && wall_dir == ray->wall_dir)
		rotate_slot(cub3d, ray);
	else if (wall_state == SLOT_RESULT && wall_dir == ray->wall_dir)
		ray->wall_img = cub3d->walls->shot_enemy;
}

int	count_frame(t_cub3d *cub3d)
{
	cub3d->frame_count++;
	if (cub3d->frame_count >= 60)
		cub3d->frame_count = 0;
	return (true);
}


void	manage_slot_flag(t_cub3d *cub3d, t_ray *ray, int y)
{
	int	is_not_door;

	is_not_door = cub3d->map[ray->map_point.y][ray->map_point.x].obj != DOOR;
	if (ray->shot_flag && cub3d->player->shot.y == y && is_not_door)
	{
		if (cub3d->slot.slot_flag)
		{
			cub3d->slot.slot_flag = false;
			if (ray->wall_img == cub3d->walls->enemy)
			{
				cub3d->map[ray->map_point.y][ray->map_point.x].state = SLOT_RESULT;
				cub3d->slot.result_flag = true;
				cub3d->slot.release_count = cub3d->frame_count;
			}
			else
				cub3d->map[ray->map_point.y][ray->map_point.x].state = OTHER;
		}
		else
		{
			cub3d->map[ray->map_point.y][ray->map_point.x].state = SLOT;
			cub3d->slot.shot_wall = ray->wall_dir;
			cub3d->slot.slot_flag = true;
			cub3d->slot.map_point.x = ray->map_point.x;
			cub3d->slot.map_point.y = ray->map_point.y;
		}
		
			ray->shot_flag = false;
	}
}
