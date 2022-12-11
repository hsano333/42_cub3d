/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 06:03:23 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 12:08:23 by hsano            ###   ########.fr       */
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
}

void	load_map_and_img(t_cub3d *cub3d, int argc, char **argv)
{
	printf("test width=40, height=30 , argc=%d, argv=%p \n", argc, argv);
	cub3d->image->width = 40;
	cub3d->image->height = 30;
	allocate_memmory_map(cub3d);
	allocate_memmory_wall(cub3d);

	//test
	load_wall_img(cub3d, cub3d->mlx, &(cub3d->walls->north), "image/koto_north.xpm");
	load_wall_img(cub3d, cub3d->mlx, &(cub3d->walls->west), "image/koto_west.xpm");
	load_wall_img(cub3d, cub3d->mlx, &(cub3d->walls->east), "image/koto_east.xpm");
	load_wall_img(cub3d, cub3d->mlx, &(cub3d->walls->south), "image/koto_south.xpm");
	load_wall_img(cub3d, cub3d->mlx, &(cub3d->walls->sprite), "image/koto_sprite.xpm");
}
