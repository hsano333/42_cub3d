/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:04:37 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:24:56 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/close.h"

void	putstr_err(const char *err_type, const char *err_message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err_type)
		write(STDERR_FILENO, err_type, ft_strlen((char *)err_type));
	write(STDERR_FILENO, err_message, ft_strlen((char *)err_message));
}

void	putstr_err_line(int line, const char *err_message)
{
	putstr_err(NULL, "Line ");
	ft_putnbr_fd(line, STDERR_FILENO);
	putstr_err(NULL, err_message);
}

void	print_file_err_exit(int err)
{
	int			n_bit;
	const char	*err_msg[] = {
	[ERR_NO_FILE] = MS_NO_FILE,
	[ERR_EXTENTION] = MS_EXTENTION,
	[ERR_FOLDER] = MS_FOLDER,
	[ERR_CHMOD] = MS_CHMOD,
	[ERR_PATH] = MS_PATH,
	};

	n_bit = -1;
	while (++n_bit < NBR_PARSING_ERR)
	{
		if ((err >> n_bit) & 1)
			putstr_err(NULL, err_msg[n_bit]);
	}
	exit(err);
}

void	print_parse_err_exit(t_parser *parser, t_cub3d *env)
{
	int			i;
	const char	*tab[] = {
	[ERR_EMPTY_FILE] = MS_EMPTY_FILE, [ERR_TX_KEY_MISS] = MS_TX_KEY_MISS,
	[ERR_TX_PATH] = MS_TX_PATH, [ERR_TX_PATH_LENGH] = MS_TX_PATH_LENGH,
	[ERR_FC_OVERFLOW] = MS_FC_OVERFLOW, [ERR_FC_KEY_MISS] = MS_FC_KEY_MISS,
	[ERR_FC_FORM] = MS_FC_FORM, [ERR_MP_MISPLACED] = MS_MP_MISPLACED,
	[ERR_MP_TOO_SMALL] = MS_MP_TOO_SMALL, [ERR_MP_NO_PLAYER] = MS_MP_NO_PLAYER,
	[ERR_MP_MULTI_PLAYER] = MS_MP_MULTI_PLAYER, [ERR_MP_CUTTED] = MS_MP_CUTTED,
	[ERR_MP_BORDERS] = MS_MP_BORDERS, [ERR_MP_TOO_BIG] = MS_MP_TOO_BIG,
	[ERR_MP_UNABLE_TO_CPY] = MS_MP_UNABLE_TO_CPY, [ERR_GIBBER] = MS_GIBBER,
	[ERR_FC_MULTIDEF] = MS_FC_MULTIDEF, [ERR_TX_MULTIDEF] = MS_TX_MULTIDEF,
	};

	i = -1;
	if (parser->err_buf[0][0])
		while (++i < parser->err_buf_index)
			putstr_err_line(parser->err_buf[i][0], tab[parser->err_buf[i][1]]);
	i = -1;
	while (++i <= ERR_TX_MULTIDEF)
		if ((parser->blocking_err_flag >> i) & 1)
			putstr_err(MS_BLK_ERR, tab[i]);
	i = -1;
	while (++i <= ERR_TX_MULTIDEF)
		if ((parser->blocking_err_flag >> i) & 1)
			add_to_env_exit(parser, env);
}
