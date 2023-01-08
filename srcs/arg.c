/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 06:03:23 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 07:29:13 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "wall.h"
#include "libft_mem.h"
#include "close.h"
#include "wall.h"

static void	allocate_memmory_map(t_cub3d *cub3d)
{
	int	i;

	cub3d->map = (t_map **)ft_calloc(sizeof(t_map *) ,cub3d->image->height);
	i = 0;
	while (i < cub3d->image->height)
	{
		cub3d->map[i] = malloc(sizeof(t_map) * cub3d->image->width);
		if (!cub3d->map[i])
			error_and_end_game(cub3d, NULL);
		i++;
	}
}

static void	allocate_memmory_wall(t_cub3d *cub3d)
{
	cub3d->walls = (t_wall_imgs *)ft_calloc(sizeof(t_wall_imgs), 1);
	if (!cub3d->walls)
		error_and_end_game(cub3d, NULL);
	cub3d->trans_walls = (t_wall_imgs *)ft_calloc(sizeof(t_wall_imgs), 1);
	if (!cub3d->trans_walls)
		error_and_end_game(cub3d, NULL);
}

void	load_map_and_img(t_cub3d *cub3d, int argc, char **argv)
{
	//test
	argc=(int)argc;
	argv=(char **)argv;

	cub3d->image->width = WIN_WIDTH;
	cub3d->image->height = WIN_HEIGHT;
	allocate_memmory_map(cub3d);
	allocate_memmory_wall(cub3d);

	//test
	cub3d->walls->north = load_wall_img(cub3d, "image/north.xpm");
	cub3d->walls->west = load_wall_img(cub3d, "image/west.xpm");
	cub3d->walls->east = load_wall_img(cub3d, "image/east.xpm");
	cub3d->walls->south = load_wall_img(cub3d, "image/south.xpm");
	cub3d->walls->sprite = load_wall_img(cub3d, "image/door.xpm");

	cub3d->trans_walls->north = load_wall_img(cub3d, "image/north.xpm");
	cub3d->trans_walls->west = load_wall_img(cub3d, "image/west.xpm");
	cub3d->trans_walls->east = load_wall_img(cub3d, "image/east.xpm");
	cub3d->trans_walls->south = load_wall_img(cub3d, "image/south.xpm");
	cub3d->trans_walls->sprite = load_wall_img(cub3d, "image/door.xpm");
}
