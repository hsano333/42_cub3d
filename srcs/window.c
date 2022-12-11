/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:29:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 12:15:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	update_image(t_cub3d *cub3d)
{
	static int i = 0;


	i++;
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->north->img, 200, 200);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->south->img, 200, 360);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->west->img, 120, 280);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->walls->east->img, 280, 280);
	/*
	if (!cub3d->update_image_flag)
		return (false);
	if (cub3d->create_image_flag)
		create_image(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, \
		   	cub3d->image_info.image, cub3d->offset.x, cub3d->offset.y);
	cub3d->update_image_flag = false;
	cub3d->create_image_flag = false;
	*/
	return (true);
}
