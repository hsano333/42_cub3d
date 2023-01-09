/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:24:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 15:48:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

static t_point	get_nearest_wall(t_cub3d *cub3d)
{
	t_point	wall;

	
	wall.x = cub3d->player->map.x;
	wall.y = 0;

	return (wall);
}

void	open_and_close_door(t_cub3d *cub3d)
{
	t_point	door_point;

	door_point = get_nearest_wall(cub3d);
	printf("open and close door:%p, %p\n", cub3d, &door_point);

}
