/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:05:22 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:03:55 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "close.h"

int	exit_game(t_cub3d *env)
{
	if (env->map)
		clear_map(env);
	(void)env;
	exit(EXIT_SUCCESS);
	return (0);
}

void	parse_map_exit(t_parser *parser)
{
	int	i;

	i = -1;
	while (++i < parser->map_buf_index)
		parser->map_buf[i] = c3d_free(parser->map_buf[i]);
}

void	add_to_env_exit(t_parser *parser, t_cub3d *env)
{
	(void)env;
	parse_map_exit(parser);
	exit_game(env);
}
