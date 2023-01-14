/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_map_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:01:08 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:25:51 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

int	check_cutted_map(t_parser *parser, t_cub3d *env)
{
	int	i;
	int	j;
	int	*map_line;

	(void)env;
	i = -1;
	j = i + 1;
	map_line = parser->map_line_buf;
	while (j < parser->map_buf_index - 1)
	{
		if (map_line[++i] + 1 != map_line[++j])
			return (update_err_flag(parser, ERR_MP_CUTTED));
	}
	return (0);
}

int	check_player(t_parser *parser, t_cub3d *env)
{
	int		player_flag;
	char	**map;
	char	*tmp;

	(void)env;
	player_flag = 0;
	map = parser->map_buf;
	while (*map)
	{
		tmp = *map++;
		while (*tmp)
		{
			if (ft_strchr(MAP_ORIENT_CHAR, *tmp))
				player_flag++;
			tmp++;
		}
	}
	if (player_flag == 0)
		return (update_err_flag(parser, ERR_MP_NO_PLAYER));
	else if (player_flag > 1)
		return (update_err_flag(parser, ERR_MP_MULTI_PLAYER));
	return (0);
}

void	free_ptrarr(void **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return ;
}
