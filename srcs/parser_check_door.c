/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:56:29 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 16:05:47 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/cub3d_parser.h"

bool	is_ok_door(t_cub3d *env, size_t y, size_t x)
{
	return (!(((env->map[y - 1][x].obj == WALL && \
				env->map[y + 1][x].obj == WALL) && \
				(env->map[y][x - 1].obj == EMPTY && \
				env->map[y][x + 1].obj == EMPTY)) || \
				((env->map[y - 1][x].obj == EMPTY && \
				env->map[y + 1][x].obj == EMPTY) && \
				(env->map[y][x - 1].obj == WALL && \
				env->map[y][x + 1].obj == WALL))));
}

bool	check_door(t_parser *parser, t_cub3d *env)
{
	size_t	y;
	size_t	x;
	bool	err_flag;

	err_flag = true;
	y = 0;
	while (env->map[y])
	{
		x = 0;
		while (env->map[y][x].obj != 100)
		{
			if (env->map[y][x].obj == DOOR)
			{
				if (is_ok_door(env, y, x))
					err_flag = false;
			}
			x++;
		}
		y++;
	}
	if (!err_flag)
		return (update_err_flag(parser, ERR_GIBBER));
	return (false);
}
