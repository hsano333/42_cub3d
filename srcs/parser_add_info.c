/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psrser_add_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 06:32:35 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 06:45:26 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/close.h"
#include "mlx.h"

int	add_info_err_buf(t_parser *parser, int type, int error_num)
{
	parser->blocking_err_flag |= (1 << error_num);
	if (type <= TYPE_C)
		parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->info_buf_line[type];
	else
		parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->gnl_cnt;
	parser->err_buf[parser->err_buf_index][ERROR_CODE] = error_num;
	parser->err_buf_index++;
	return (-1);
}
