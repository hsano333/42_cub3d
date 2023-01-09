/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_check_buf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:19:45 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:19:45 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

void pick_line_set_type(int fd, t_parser *parser)
{

    parser->line = get_next_line(fd);
    parser->gnl_cnt++;
    printf("parser-line: %s\n", parser->line);
    while (check_type(parser->line, &parser->type) == TYPE_USELESS)
    {
        free(parser->line);
        parser->line = get_next_line(fd);
        parser->gnl_cnt++;
    }
}

int add_in_err_buf(t_parser *parser, int error_type)
{
    if (parser->err_buf_index < PARSER_BUFFER_SIZE)
    {
        parser->err_buf[parser->err_buf_index][0] = parser->gnl_cnt;
        parser->err_buf[parser->err_buf_index][1] = error_type;
        parser->err_buf_index++;
    }
    if (error_type < ERR_GIBBER)
        parser->blocking_err_flag |= (1 << error_type);
    if (parser->line && parser->type != TYPE_MAP)
    {
        free(parser->line);
        parser->line = NULL;
    }
    return (1);
}

void check_missing_info(t_parser *parser, int flag)
{
    int tmp;

    tmp = flag;
    flag &= ~15;
    tmp -= flag;
    if ((tmp != 15))
        parser->blocking_err_flag |= (1 << ERR_TX_KEY_MISS);
    flag |= 15;
    if ((flag != 63))
        parser->blocking_err_flag |= (1 << ERR_FC_KEY_MISS);
}

int fill_parser_buf(t_parser *parser, int fd)
{
    if (fd > -1)
    {
        pick_line_set_type(fd, parser);
        while (parser->type != TYPE_EOF)
        {
            parse_line(parser, parser->line);
            if (parser->type == TYPE_MAP && parser->info_buf_flag != 63)
                add_info_err_buf(parser, TYPE_MAP, ERR_MP_MISPLACED);
            pick_line_set_type(fd, parser);
        }
        if (parser->gnl_cnt == 1)
            add_in_err_buf(parser, ERR_EMPTY_FILE);
        close(fd);
    }
    if (parser->info_buf_flag != 63)
        check_missing_info(parser, parser->info_buf_flag);
    return (parser->blocking_err_flag);
}