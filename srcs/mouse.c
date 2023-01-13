/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:50:01 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 14:16:14 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mouse.h"
#include "cub3d.h"
#include "libft_mem.h"
#include "libft_str.h"

int	hook_mouse_hook(int key, int x, int y, void *cub3d_v)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_v;
	cub3d = (t_cub3d *)cub3d;
	key = (int)key;
	if (key == 3)
		cub3d->player->dir.degree += cub3d->angles[x].degree;
	if (key == 1)
	{
		cub3d->player->shot.x = x;
		cub3d->player->shot.y = y;
	}
	if (cub3d->player->dir.degree >= 360)
		cub3d->player->dir.degree -= 360;
	if (cub3d->player->dir.degree < 0)
		cub3d->player->dir.degree += 360;
	return (true);
}
