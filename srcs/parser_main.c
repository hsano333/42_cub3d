/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:02:56 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:17:08 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

int	update_err_flag(t_parser *parser, int err_nbr)
{
	parser->blocking_err_flag |= (1 << err_nbr);
	return (parser->blocking_err_flag);
}

char	**freetab_index(char **tab, int index, int opt)
{
	int	i;

	i = -1;
	if (opt)
	{
		while (++i < index)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
	else
	{
		while (tab[++i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
	}
	return (NULL);
}

void	parse_map_main(t_cub3d *env, char **argv)
{
	int			fd;
	t_parser	parser;

	fd = -1;
	ft_memset(&parser, 0, sizeof(t_parser));
	if (check_file(argv + 1, &fd, &parser))
		print_file_err_exit(parser.blocking_err_flag);
	else if (fill_parser_buf(&parser, fd))
		print_parse_err_exit(&parser, env);
	else if (add_to_env(&parser, env))
		print_parse_err_exit(&parser, env);
	freetab_index(parser.map_buf, parser.map_buf_index, WITH_INDEX);
}
