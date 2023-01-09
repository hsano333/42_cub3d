/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:46:39 by hsano             #+#    #+#             */
/*   Updated: 2023/01/09 07:58:09 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key.h"
#include "close.h"
#include "stdio.h"
#include "door.h"
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

static int	is_invalid_point(t_cub3d *cub3d, size_t x, size_t y)
{
	t_point	tmp_map_point;
	t_point	tmp_mass_point;

	tmp_map_point.x = (int)(x / MAP_SPACE);
	tmp_map_point.y = (int)(y / MAP_SPACE);
	if (tmp_map_point.x < 0 || tmp_map_point.y < 0)
		return (true);
	if (cub3d->map[tmp_map_point.y][tmp_map_point.x].obj == WALL \
		|| (cub3d->map[tmp_map_point.y][tmp_map_point.x].obj >= DOOR && cub3d->map[tmp_map_point.y][tmp_map_point.x].state == CLOSE))
		return (true);
	tmp_mass_point.x = (int)(x % MAP_SPACE);
	tmp_mass_point.y = (int)(y % MAP_SPACE);
	if (tmp_mass_point.x == 0)
		tmp_map_point.x -= 1;
	if (tmp_mass_point.y == 0)
		tmp_map_point.y -= 1;
	if (cub3d->map[tmp_map_point.y][tmp_map_point.x].obj == WALL \
			|| (cub3d->map[tmp_map_point.y][tmp_map_point.x].obj >= DOOR && cub3d->map[tmp_map_point.y][tmp_map_point.x].state == CLOSE))
		return (true);
	return (false);
}

static void	change_player_point(t_cub3d *cub3d, int x, int y)
{
	size_t	tmp_point_x;
	size_t	tmp_point_y;

	tmp_point_x = cub3d->player->world_x + x;
	tmp_point_y = cub3d->player->world_y + y;
	if (is_invalid_point(cub3d, tmp_point_x, tmp_point_y))
		return ;
	cub3d->player->map.x = (int)(tmp_point_x / MAP_SPACE);
	cub3d->player->map.y = (int)(tmp_point_y / MAP_SPACE);
	cub3d->player->mass.x = (int)(tmp_point_x % MAP_SPACE);
	cub3d->player->mass.y = (int)(tmp_point_y % MAP_SPACE);
	//printf("map:x=%d, y=%d, mass:x=%d, y=%d\n",cub3d->player->map.x, cub3d->player->map.y,cub3d->player->mass.x, cub3d->player->mass.y );
}

int	key_hook(int key, void *cub3d)
{
	double	angle;
	const	double	step = MAP_SPACE / MOVE_STEP;

	cub3d = (t_cub3d *)cub3d;
	angle = ((t_cub3d *)cub3d)->player->dir.radian;
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
		change_player_point(cub3d, -sin(angle) * step, -cos(angle) * step);
	else if (key == S_KEY)
		change_player_point(cub3d, sin(angle) * step, cos(angle) * step);
	else if (key == A_KEY)
		change_player_point(cub3d, -cos(angle) * step, sin(angle) * step);
	else if (key == D_KEY)
		change_player_point(cub3d, cos(angle) * step, -sin(angle) * step);
	else if (key == SPACE_KEY)
		open_and_close_door(cub3d);
	else
		printf("not defined key=%d\n", key);
	return (true);
}
