/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:12:40 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 22:54:08 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

static int	check_extention(char *file)
{
	char	*dot;
	char	*tmp;
	int		ret;

	ret = 0;
	if (file)
	{
		dot = ft_strrchr(file, '.');
		tmp = dot + 1;
		if (dot == 0 || ft_strncmp(tmp, "cub", 4) != 0)
			return (ret | (1 << ERR_EXTENTION));
		return (0);
	}
	return (ret | 1 << ERR_EXTENTION);
}

static int	check_if_folder(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1 << ERR_FOLDER);
	}
	return (0);
}

int	check_file(char **av, int *fd, t_parser *parser)
{
	if (*av)
	{
		parser->blocking_err_flag += check_extention(av[0]);
		parser->blocking_err_flag += check_if_folder(av[0]);
		*fd = open(av[0], O_RDONLY);
		if (*fd == -1 && !parser->blocking_err_flag)
		{
			if (errno == EACCES)
				parser->blocking_err_flag |= (1 << ERR_CHMOD);
			else if (errno == EACCES)
				parser->blocking_err_flag |= (1 << ERR_PATH);
			else
			{
				perror("cub3d");
				exit(errno);
			}
		}
	}
	else
		parser->blocking_err_flag |= (1 << ERR_NO_FILE);
	return (parser->blocking_err_flag);
}
