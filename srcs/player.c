/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:39:41 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 12:13:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_map_obj	get_cur_map_obj(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = cub3d->player->map.x;
	y = cub3d->player->map.y;
	return (cub3d->map[y][x].obj);
}

t_wpoint	get_dist_player_from_wall(t_cub3d *cub3d, t_point map \
								, double angle)
					
{
	t_wpoint	dist;

	if (angle < M_PI / 2 || angle > M_PI * 3 / 2)
		dist.y = cub3d->player->world_y - map.y * WALL_LEN;
	else
		dist.y = (map.y + 1) * WALL_LEN - cub3d->player->world_y;
	if (angle < M_PI && angle > 0)
		dist.x = cub3d->player->world_x - map.x * WALL_LEN;
	else
		dist.x = (map.x + 1) * WALL_LEN - cub3d->player->world_x;
	return (dist);
}
