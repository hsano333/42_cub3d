/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:08:57 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 00:43:50 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wall.h"
#include "close.h"
#include "libft_mem.h"

t_image	*load_wall_img(t_cub3d *cub3d, char *path)
{
	t_image	*wall;

	wall = (t_image *)ft_calloc(sizeof(t_image), 1);
	if (!wall)
		error_and_end_game(cub3d, NULL);
	wall->img = mlx_xpm_file_to_image(cub3d->mlx \
							, path, &(wall->width), &(wall->height));
	if (!wall->img)
		error_and_end_game(cub3d, "cub3d:can't load image file\n");
	wall->addr = mlx_get_data_addr(wall->img, &(wall->bpp) \
										, &(wall->sl), &(wall->endian));
	return (wall);
}
