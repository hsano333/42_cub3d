/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:10:56 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 22:14:59 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/all.h"

void	draw_square(t_cub3d *env, int startx, int starty, int color)
{
	const int	wall = 4;
	int			y;
	int			x;
	int			*image_addr;

	image_addr = env->image->addr;
	y = 0;
	while (y < wall)
	{
		x = 0;
		while (x < wall)
		{
			image_addr[(starty * wall + y) * WIN_WIDTH \
				+ (startx * wall + x)] = color;
			x++;
		}
		y++;
	}
}

void	draw_map(t_cub3d *env, t_map **map, int player_x, int player_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x].obj != 100)
		{
			if (map[y][x].obj == WALL || map[y][x].obj == DOOR || \
					(y == player_y && x == player_x))
			{
				if (map[y][x].obj == WALL)
					color = 0xFFFFFF;
				else
					color = 0xFF0000;
				draw_square(env, 5 + x, 5 + y, color);
			}
			x++;
		}
		y++;
	}
}
