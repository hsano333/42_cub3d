/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:46:39 by hsano             #+#    #+#             */
/*   Updated: 2022/12/29 05:07:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key.h"
#include "close.h"
#include "stdio.h"
#include <math.h>


static void	change_player_dir(t_cub3d * cub3d, int added_angle)
{
	cub3d->player->dir.degree += added_angle;
	if (cub3d->player->dir.degree >= 360)
		cub3d->player->dir.degree -= 360;
	else if (cub3d->player->dir.degree < 0)
		cub3d->player->dir.degree += 360;
	cub3d->player->dir.radian = cub3d->player->dir.degree * M_PI / 180;
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
		;
	else if (key == A_KEY)
		;
	else if (key == S_KEY)
		;
	else if (key == D_KEY)
		;
	else
		printf("not defined key=%d\n", key);
	printf("press key=%d\n", key);
	return (true);
}
