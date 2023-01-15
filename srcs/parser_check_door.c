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

bool check_door(t_parser *parser)
{
    size_t y;
    size_t x;
    bool err_flag;

    err_flag = false;
    y = 0;
    while (parser->map_buf[y])
    {
        x = 0;
        while (parser->map_buf[y][x] != '\n')
        {
            if (parser->map_buf[y][x] == 'D')
            {
                printf("y: %zu x: %zu\n", y, x);
                if (!((parser->map_buf[y - 1][x] == '1' || parser->map_buf[y + 1][x] == '1') && (parser->map_buf[y][x - 1] == '0' || parser->map_buf[y][x + 1] == '0')) || ((parser->map_buf[y - 1][x] == '0' || parser->map_buf[y + 1][x] == '0') && (parser->map_buf[y][x - 1] == '1' || parser->map_buf[y][x + 1] == '1')))
                {
                    err_flag = true;
                    break;
                }
            }
            x++;
        }
        y++;
    }
    printf("check door: %d\n", err_flag);
    if (err_flag)
        return (update_err_flag(parser, ERR_GIBBER));
    return (true);
}