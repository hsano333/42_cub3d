/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:08:13 by hsano             #+#    #+#             */
/*   Updated: 2022/12/17 18:32:08 by hsano            ###   ########.fr       */
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

void	clear_wall(t_cub3d *cub3d, t_wall_imgs *walls)
{
	if (walls)
	{
		if (walls->north && walls->north->img)
			mlx_destroy_image(cub3d->mlx, walls->north->img);
		if (walls->south && walls->south->img)
			mlx_destroy_image(cub3d->mlx, walls->south->img);
		if (walls->west && walls->west->img)
			mlx_destroy_image(cub3d->mlx, walls->west->img);
		if (walls->east && walls->east->img)
			mlx_destroy_image(cub3d->mlx, walls->east->img);
		if (walls->sprite && walls->sprite->img)
			mlx_destroy_image(cub3d->mlx, walls->sprite->img);
		free(walls->north);
		free(walls->south);
		free(walls->west);
		free(walls->east);
		free(walls->sprite);
		free(walls);
	}
}

void	clear_cub3d(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->map)
		clear_map(cub3d);
	if (cub3d->image && cub3d->image->img)
		mlx_destroy_image(cub3d->mlx, cub3d->image->img);
	free(cub3d->image);
	clear_wall(cub3d, cub3d->walls);
	clear_wall(cub3d, cub3d->trans_walls);
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	if (cub3d->player)
		free(cub3d->player);
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
