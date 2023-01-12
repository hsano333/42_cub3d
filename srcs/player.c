/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:39:41 by hsano             #+#    #+#             */
/*   Updated: 2023/01/12 07:52:25 by hsano            ###   ########.fr       */
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
