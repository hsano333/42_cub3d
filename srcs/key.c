/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:46:39 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 09:52:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key.h"
#include "close.h"
#include "stdio.h"
#include <math.h>


static void	change_player_dir(t_cub3d *cub3d, int added_angle)
{
	cub3d->player->dir.degree += added_angle;
	if (cub3d->player->dir.degree >= 360)
		cub3d->player->dir.degree -= 360;
	else if (cub3d->player->dir.degree < 0)
		cub3d->player->dir.degree += 360;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
}

static void	change_player_place(t_cub3d *cub3d, int x, int y)
{
	size_t	tmp_point_x;
	size_t	tmp_point_y;
	t_point	tmp_map_point;

	printf("change No.1 map:x=%d, y=%d, mass:x=%d, y=%d\n", cub3d->player->map.x, cub3d->player->map.y, cub3d->player->mass.x, cub3d->player->mass.y);
	tmp_point_x = cub3d->player->world_x + x;
	tmp_point_y = cub3d->player->world_y + y;
	tmp_map_point.x = (int)(tmp_point_x / MAP_SPACE);
	tmp_map_point.y = (int)(tmp_point_y / MAP_SPACE);
	if (cub3d->map[tmp_map_point.y][tmp_map_point.x].obj == WALL || cub3d->map[tmp_map_point.y][tmp_map_point.x].obj >= DOOR)
		return ;
	cub3d->player->map.x = (int)(tmp_point_x / MAP_SPACE);
	cub3d->player->map.y = (int)(tmp_point_y / MAP_SPACE);
	cub3d->player->mass.x = (int)(tmp_point_x % MAP_SPACE);
	cub3d->player->mass.y = (int)(tmp_point_y % MAP_SPACE);
	//if (tmp_point.x >= MAP_SPACE)
		//tmp_point.x -= MAP_SPACE;
	//else if (tmp_point.x < 0)
		//tmp_point.x += MAP_SPACE;
	//cub3d->player->mass.y += y;
	printf("change No.2 map:x=%d, y=%d, mass:x=%d, y=%d\n", cub3d->player->map.x, cub3d->player->map.y, cub3d->player->mass.x, cub3d->player->mass.y);

}

int	key_hook(int key, void *cub3d)
{
	if (((t_cub3d *)cub3d)->lock)
		return (false);
	if (key == ESC)
		close_cub3d(cub3d);
	else if (key == ARROW_LEFT)
		change_player_dir(cub3d, 3);
	else if (key == ARROW_RIGHT)
		change_player_dir(cub3d, -3);
	else if (key == ARROW_UP)
		;
	else if (key == ARROW_DOWN)
		;
	else if (key == W_KEY)
		change_player_place(cub3d, 0, -(MAP_SPACE / MOVE_STEP));
	else if (key == A_KEY)
		change_player_place(cub3d, -(MAP_SPACE / MOVE_STEP), 0);
	else if (key == S_KEY)
		change_player_place(cub3d, (MAP_SPACE / MOVE_STEP), 0);
	else if (key == D_KEY)
		change_player_place(cub3d, 0, (MAP_SPACE / MOVE_STEP));
	else
		printf("not defined key=%d\n", key);
	//printf("press key=%d\n", key);
	return (true);
}
