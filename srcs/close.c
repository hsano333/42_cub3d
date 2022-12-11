/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:08:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 12:07:55 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdlib.h"
#include "mlx.h"
#include "libft_put.h"

void	clear_map(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d->map)
		return ;
	i = 0;
	while (i < cub3d->image->height)
	{
		free(cub3d->map[i]);
		cub3d->map[i] = 0;
		i++;
	}
	free(cub3d->map);
	cub3d->map = 0;
}

void	clear_image_and_wall(t_cub3d *cub3d)
{
	if (cub3d->image)
		mlx_destroy_image(cub3d->mlx, cub3d->image->img);
	free(cub3d->image);
	if (cub3d->walls)
	{
		if (cub3d->walls->north && cub3d->walls->north->img)
			mlx_destroy_image(cub3d->mlx, cub3d->walls->north->img);
		if (cub3d->walls->south && cub3d->walls->south->img)
			mlx_destroy_image(cub3d->mlx, cub3d->walls->south->img);
		if (cub3d->walls->west && cub3d->walls->west->img)
			mlx_destroy_image(cub3d->mlx, cub3d->walls->west->img);
		if (cub3d->walls->east && cub3d->walls->east->img)
			mlx_destroy_image(cub3d->mlx, cub3d->walls->east->img);
		if (cub3d->walls->sprite && cub3d->walls->sprite->img)
			mlx_destroy_image(cub3d->mlx, cub3d->walls->sprite->img);
		free(cub3d->walls->north);
		free(cub3d->walls->south);
		free(cub3d->walls->west);
		free(cub3d->walls->east);
		free(cub3d->walls->sprite);
		free(cub3d->walls);
	}
}

void	clear_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->map)
		clear_map(cub3d);
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	clear_image_and_wall(cub3d);
	free(cub3d);
}

void	error_and_end_game(t_cub3d *cub3d, char *str)
{
	if (cub3d)
		clear_cub3d(cub3d);
	if (str)
		ft_putstr_fd(str, 2);
	else
		perror("cub3d:");
	exit(1);
}

int	close_cub3d(t_cub3d *cub3d)
{
	clear_cub3d(cub3d);
	exit(0);
}
