/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:20:21 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/08 22:20:21 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

void set_player_dir(t_player *player, char orient)
{
    // orient 方向
    if (orient == 'N' || orient == 'S')
    {
        if (orient == 'N')
            player->dir.degree = 0;
        else
            player->dir.degree = 180;
    }
    else if (orient == 'W' || orient == 'E')
    {
        if (orient == 'W')
            player->dir.degree = 90;
        else
            player->dir.degree = 270;
    }
}

int update_player_position(t_cub3d *env, char **map)
{
    int y;
    int x;

    y = -1;
    printf("update_player\n");
    while (map[++y])
    {
        x = -1;
        while (map[y][++x] != '\n')
        {
            if (ft_strchr("SEWN", map[y][x]))
            {
                env->player->map.x = x;
                env->player->map.y = y;
                printf("player: %d\n", env->player->map.x);
                printf("player: %d\n", env->player->map.y);

                set_player_dir(env->player, map[y][x]);
                // ここはどうするか後で考える
                // map[y][x] = '0';
                env->map[y][x].obj = 0;
                return (0);
            }
        }
    }
    return (-1);
}
