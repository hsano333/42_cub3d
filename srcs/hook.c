/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 07:04:07 by hsano             #+#    #+#             */
/*   Updated: 2022/12/17 15:34:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "mlx_int.h"
#include "close.h"
#include "mlx.h"
#include "libft_mem.h"
#include "libft_str.h"
#include "key.h"
#include "mouse.h"
#include "window.h"
#include "ray.h"

int	expose_win_hook(void *p)
{
	t_cub3d	*cub3d;

	cub3d = p;
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image->img, 0, 0);
	return (true);
}


static	int	unlock(t_cub3d *cub3d)
{
	cub3d->lock = false;
	return (true);
}


void	init_mlx_hook(t_cub3d *cub3d)
{
	mlx_expose_hook(cub3d->window, expose_win_hook, cub3d);
	mlx_mouse_hook(cub3d->window, hook_mouse_hook, cub3d);
	mlx_key_hook(cub3d->window, key_hook, cub3d);
	mlx_hook(cub3d->window, ON_DESTROY, NoEventMask, close_cub3d, cub3d);
	mlx_hook(cub3d->window, ON_EXPOSE, NoEventMask, unlock, cub3d);
	mlx_loop_hook(cub3d->mlx, fire_ray, cub3d);
	mlx_loop_hook(cub3d->mlx, update_image, cub3d);
}
