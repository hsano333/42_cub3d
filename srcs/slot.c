/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:14:27 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 07:12:18 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slot.h"
#include "door.h"

int	is_raise_shot_flag(t_cub3d *cub3d, t_ray *ray,  int start, int end)
{
	t_point	cur;
	t_point	old;
	int	is_same_wall;

	if (cub3d->slot.result_flag)
		return (false);

	cur = ray->map_point;
	old = cub3d->slot.map_point;
	//is_same_wall = cur.x == old.x && cur.y == old.y && cub3d->slot.shot_wall == ray->wall_dir;
	is_same_wall = cur.x == old.x && cub3d->slot.shot_wall == ray->wall_dir;
	if (cub3d->slot.slot_flag == false || is_same_wall)
	{
		if (start <= cub3d->player->shot.x && cub3d->player->shot.x <= end)
			return (true);
	}
	return (false);
}

void	change_image(t_cub3d *cub3d, t_ray *ray, t_point next)
{
	if (ray->is_door)
		ray->wall_img = cub3d->walls->door;
	ray->is_door = false;
	if (cub3d->map[next.y][next.x].obj >= DOOR)
	{
		open_and_close_door(cub3d, next);
		ray->wall_img = cub3d->walls->door;
		//ray->is_door = true;
	}
	//printf("No.1 cub3d->map[next.y][next.x].state=%d\n", cub3d->map[next.y][next.x].state);
	if (cub3d->map[next.y][next.x].state == SLOT && cub3d->slot.shot_wall == ray->wall_dir)
	{
		if (cub3d->slot.result_flag)
			printf("shot result No.3, y=%d,x=%d \n", next.y, next.x);
			//printf("slot result No.0\n");
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
	else if (cub3d->map[next.y][next.x].state == SLOT_RESULT && cub3d->slot.shot_wall == ray->wall_dir)
	{
			printf("shot result No.4, y=%d,x=%d \n", next.y, next.x);
		ray->wall_img = cub3d->walls->shot_enemy;
	}
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


}
