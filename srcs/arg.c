/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 06:03:23 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 21:25:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "wall.h"
#include "libft_mem.h"
#include "close.h"
#include "wall.h"

static void	allocate_memmory_wall(t_cub3d *cub3d)
{
	cub3d->walls = (t_wall_imgs *)ft_calloc(sizeof(t_wall_imgs), 1);
	if (!cub3d->walls)
		error_and_end_game(cub3d, NULL);
}

void	load_map_and_img(t_cub3d *cub3d, int argc, char **argv)
{
	argc = (int)argc;
	argv = (char **)argv;
	cub3d->image->width = WIN_WIDTH;
	cub3d->image->height = WIN_HEIGHT;
	allocate_memmory_wall(cub3d);
	cub3d->walls->north = load_wall_img(cub3d, "image/north.xpm");
	cub3d->walls->west = load_wall_img(cub3d, "image/west.xpm");
	cub3d->walls->east = load_wall_img(cub3d, "image/east.xpm");
	cub3d->walls->south = load_wall_img(cub3d, "image/south.xpm");
	cub3d->walls->door = load_wall_img(cub3d, "image/door.xpm");
}
