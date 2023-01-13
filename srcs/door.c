/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 21:54:23 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include "ray.h"
#include "window.h"
#include "libft_mem.h"

static int	is_nearest_wall(t_cub3d *cub3d, t_point next)
{
	if (next.x - cub3d->player->map.x == 1 \
			|| next.x - cub3d->player->map.x == -1)
	{
		if (next.y - cub3d->player->map.y == 0)
		{
			return (true);
		}
	}
	else if (next.y - cub3d->player->map.y == 1 \
			|| next.y - cub3d->player->map.y == -1)
	{
		if (next.x - cub3d->player->map.x == 0)
		{
			return (true);
		}
	}
	return (false);
}

static int	is_near_door(t_cub3d *cub3d)
{
	t_point	p;

	p = cub3d->player->mass;
	if (p.x <= MAP_SPACE / 4)
	{
		if (p.y >= MAP_SPACE / 4 && p.y <= MAP_SPACE * 3 / 4)
			return (true);
	}
	else if (p.x >= MAP_SPACE * 3 / 4)
	{
		if (p.y >= MAP_SPACE / 4 && p.y <= MAP_SPACE * 3 / 4)
			return (true);
	}
	if (p.y <= MAP_SPACE / 4)
	{
		if (p.x >= MAP_SPACE / 4 && p.x <= MAP_SPACE * 3 / 4)
			return (true);
	}
	if (p.y <= MAP_SPACE * 3 / 4)
	{
		if (p.x >= MAP_SPACE / 4 && p.x <= MAP_SPACE * 3 / 4)
			return (true);
	}
	return (false);
}

void	open_and_close_door(t_cub3d *cub3d, t_point next)
{
	if (!cub3d->door_change_flag)
		return ;
	if (!is_nearest_wall(cub3d, next))
		return ;
	if (!is_near_door(cub3d))
		return ;
	if (cub3d->map[next.y][next.x].state == OPEN)
		cub3d->map[next.y][next.x].state = CLOSE;
	else
		cub3d->map[next.y][next.x].state = OPEN;
	cub3d->door_change_flag = false;
}
