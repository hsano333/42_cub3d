/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 02:50:57 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 22:11:29 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "close.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "stdlib.h"
#include "mlx.h"
#include "mlx_int.h"
#include "wall.h"
#include "arg.h"
#include "hook.h"
#include "unistd.h"

void	calc_angles(t_cub3d *cub3d)
{
	int		i;
	double	ratio;

	i = 0;
	i = 0;
	while (i < WIN_WIDTH)
	{
		ratio = (double)(WIN_WIDTH / 2 - i) / BASE_ZX;
		cub3d->angles[i].radian = atan(ratio);
		if (cub3d->angles[i].radian < 0)
			cub3d->angles[i].radian += 2 * M_PI;
		cub3d->angles[i].degree = cub3d->angles[i].radian * 180 / M_PI;
		i++;
	}
}

t_cub3d	*init_minilibx(void)
{
	t_cub3d	*cub3d;

	cub3d = ft_calloc(sizeof(t_cub3d), 1);
	if (!cub3d)
		error_and_end_game(NULL, NULL);
	ft_memset(cub3d, 0, sizeof(cub3d));
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		error_and_end_game(cub3d, "cub3D:failure to init minilix\n");
	cub3d->window = mlx_new_window(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!cub3d->window)
		error_and_end_game(cub3d, "cub3D:failure to create windows\n");
	cub3d->image = (t_image *)malloc(sizeof(t_image));
	if (!cub3d->image)
		error_and_end_game(cub3d, NULL);
	cub3d->image->width = WIN_WIDTH;
	cub3d->image->height = WIN_HEIGHT;
	cub3d->image->img = (void *)mlx_new_image(cub3d->mlx \
				, cub3d->image->width, cub3d->image->height);
	if (!cub3d->image->img)
		error_and_end_game(cub3d, "cub3D:failure to create image\n");
	cub3d->image->addr = mlx_get_data_addr(cub3d->image->img, \
			&cub3d->image->bpp, &cub3d->image->sl, &cub3d->image->endian);
	return (cub3d);
}

t_cub3d	*init(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		error_and_end_game(NULL, "cub3D:invalid argument\n");
	cub3d = init_minilibx();
	cub3d->player = (t_player *)ft_calloc(sizeof(t_player), 1);
	if (!cub3d->player)
		error_and_end_game(cub3d, "cub3D:failure to create player\n");
	calc_angles(cub3d);
	parse_map_main(cub3d, argv);
	init_mlx_hook(cub3d);
	cub3d->player->mass.x = 200;
	cub3d->player->mass.y = 200;
	cub3d->player->shot.x = -1;
	cub3d->player->shot.y = -1;
	cub3d->walls->door = load_wall_img(cub3d, "image/door.xpm");
	cub3d->walls->enemy = load_wall_img(cub3d, "image/enemy.xpm");
	cub3d->walls->shot_enemy = load_wall_img(cub3d, "image/shot_enemy.xpm");
	return (cub3d);
}
