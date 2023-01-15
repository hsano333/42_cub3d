/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:32:35 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 13:48:34 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

static bool	floodfill(t_parser *parser, bool **filled_map, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= parser->map_max_y || j < 0 || j >= parser->map_max_x)
		return (false);
	if (parser->map_buf[i][j] == '1' || filled_map[i][j] == true)
		return (true);
	else
		filled_map[i][j] = true;
	is_surrounded = true;
	is_surrounded &= floodfill(parser, filled_map, i - 1, j);
	is_surrounded &= floodfill(parser, filled_map, i + 1, j);
	is_surrounded &= floodfill(parser, filled_map, i, j - 1);
	is_surrounded &= floodfill(parser, filled_map, i, j + 1);
	return (is_surrounded);
}

void	set_player_position(t_parser *parser, int *x, int *y)
{
	char	**map;
	int		i;
	int		j;

	map = parser->map_buf;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n')
		{
			if (ft_strchr(MAP_ORIENT_CHAR, map[i][j]))
			{
				*y = i;
				*x = j;
				return ;
			}
			j++;
		}
		i++;
	}
	*x = -1;
	*y = -1;
	return ;
}

int	check_map_surrounded_with_floodfill_helper(t_parser *parser)
{
	int		x;
	int		y;
	int		i;
	bool	**filled_map;
	bool	is_surrounded;

	set_player_position(parser, &x, &y);
	filled_map = ft_calloc(parser->map_max_y + 1, sizeof(bool *));
	if (!filled_map)
		return (-1);
	i = 0;
	while (i < parser->map_max_y)
	{
		filled_map[i] = ft_calloc(parser->map_max_x, sizeof(bool));
		if (!filled_map[i++])
		{
			free_ptrarr((void **)filled_map);
			return (update_err_flag(parser, ERR_MP_BORDERS));
		}
	}
	is_surrounded = floodfill(parser, filled_map, y, x);
	free_ptrarr((void **)filled_map);
	if (!is_surrounded)
		return (update_err_flag(parser, ERR_MP_BORDERS));
	return (0);
}

int	check_map_surrounded_with_floodfill(t_parser *parser, t_cub3d *env)
{
	(void)env;
	return (check_map_surrounded_with_floodfill_helper(parser));
}

int	add_map_to_env(t_parser *parser, t_cub3d *env)
{
	int	i;
	int	((*check_map[4])(t_parser *parser, t_cub3d *env));

	check_map[0] = &check_player;
	check_map[1] = &check_cutted_map;
	check_map[2] = &cpy_map_to_env;
	check_map[3] = &check_map_surrounded_with_floodfill;
	i = -1;
	if (parser->map_max_x < 3 || parser->map_max_y < 3)
		return (update_err_flag(parser, ERR_MP_TOO_SMALL));
	env->image->height = parser->map_max_y;
	env->image->width = parser->map_max_x;
	while (++i < 4)
	{
		if (check_map[i](parser, env))
			return (-1);
	}
	if (check_door(parser))
		return (-1);
	update_player_position(env, parser->map_buf);
	return (0);
}
