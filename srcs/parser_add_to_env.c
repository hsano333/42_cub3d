/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_to_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:30:23 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 06:43:50 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/close.h"
#include "mlx.h"

int	load_texture(t_cub3d *env, char *path, t_image **wall)
{
	if (!path)
		return (-1);
	*wall = (t_image *)ft_calloc(sizeof(t_image), 1);
	if (!(*wall))
		return (-1);
	(*wall)->img = mlx_xpm_file_to_image(env->mlx, \
			path, &((*wall)->width), &((*wall)->height));
	if (!(*wall)->img)
	{
		free(*wall);
		*wall = NULL;
		return (-1);
	}
	(*wall)->addr = mlx_get_data_addr((*wall)->img, \
			&((*wall)->bpp), &((*wall)->sl), &((*wall)->endian));
	return (0);
}

int	load_textures(t_parser *parser, t_cub3d *env)
{
	if (load_texture(env, parser->info_buf[0], &(env->walls->north)))
		return (-1);
	if (load_texture(env, parser->info_buf[1], &(env->walls->south)))
		return (-1);
	if (load_texture(env, parser->info_buf[2], &(env->walls->west)))
		return (-1);
	if (load_texture(env, parser->info_buf[3], &(env->walls->east)))
		return (-1);
	return (0);
}

static void	allocate_memmory_wall(t_cub3d *cub3d)
{
	cub3d->walls = (t_wall_imgs *)ft_calloc(sizeof(t_wall_imgs), 1);
	if (!cub3d->walls)
		error_and_end_game(cub3d, NULL);
}

int	add_path_to_env(t_parser *parser, t_cub3d *env)
{
	int	load_test_ret;

	allocate_memmory_wall(env);
	load_test_ret = load_textures(parser, env);
	if (load_test_ret)
		return (add_info_err_buf(parser, load_test_ret, ERR_TX_PATH));
	return (0);
}

int	add_to_env(t_parser *parser, t_cub3d *env)
{
	int	i;
	int	((*add_to_env[3])(t_parser *parser, t_cub3d *env));

	add_to_env[0] = &add_path_to_env;
	add_to_env[1] = &add_color_to_env;
	add_to_env[2] = &add_map_to_env;
	i = -1;
	while (++i < 3)
	{
		if (add_to_env[i](parser, env))
			return (parser->blocking_err_flag);
	}
	return (0);
}
