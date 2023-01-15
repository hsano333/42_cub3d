/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:56:29 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/15 12:56:29 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/cub3d_parser.h"

bool is_ok_door(t_parser *parser, size_t y, size_t x)
{
    return (!(((parser->map_buf[y - 1][x] == '1' && parser->map_buf[y + 1][x] == '1') && (parser->map_buf[y][x - 1] == '0' && parser->map_buf[y][x + 1] == '0')) || ((parser->map_buf[y - 1][x] == '0' && parser->map_buf[y + 1][x] == '0') && (parser->map_buf[y][x - 1] == '1' && parser->map_buf[y][x + 1] == '1'))));
}

bool check_door(t_parser *parser)
{
    size_t y;
    size_t x;
    bool err_flag;

    err_flag = true;
    y = 0;
    while (parser->map_buf[y])
    {
        x = 0;
        while (parser->map_buf[y][x] != '\n')
        {
            if (parser->map_buf[y][x] == 'D')
            {
                if (is_ok_door(parser, y, x))
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