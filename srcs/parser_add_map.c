/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:32:35 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:32:35 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

int check_cutted_map(t_parser *parser, t_cub3d *env)
{
    int i;
    int j;
    int *map_line;

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

int check_player(t_parser *parser, t_cub3d *env)
{
    int player_flag;
    char **map;
    char *tmp;

    // 不要
    (void)env;
    player_flag = 0;
    map = parser->map_buf;
    while (*map)
    {
        tmp = *map++;
        while (*tmp)
        {
            //==FOUND
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

/*
int check_surrounding_cells(char **map, int x, int y, int map_y)
{
    if (x == 0 || y == 0 || y == map_y - 1)
        return (-1);
    if ((map[y][x + 1] == '\0' || map[y][x + 1] == ' ') || (map[y][x - 1] == '\0' || map[y][x - 1] == ' ') || (map[y + 1][x] == '\0' || map[y + 1][x] == ' ') || (map[y - 1][x] == '\0' || map[y - 1][x] == ' '))
        return (-1);
    return (0);
}


int check_if_open_map(t_parser *parser, t_cub3d *env)
{
    int y;
    int x;
    char **map;

    (void)env;

    // map = env->map;
    map = parser->map_buf;
    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
        {
            //==FOUND
            if (ft_strchr("0SEWN", map[y][x]) && check_surrounding_cells(map, x, y, parser->map_max_y))
                return (update_err_flag(parser, ERR_MP_BORDERS)); // add?
        }
    }
    return (0);
}
*/

void free_ptrarr(void **ptr)
{
    size_t i = 0;

    while (ptr[i])
    {
        free(ptr[i]);
        ptr[i] = NULL;
        i++;
    }
    free(ptr);
    ptr = NULL;
    return;
}

static bool floodfill(t_parser *parser, bool **filled_map, int i, int j)
{
    bool is_surrounded;

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

void set_player_position(t_parser *parser, int *x, int *y)
{
    char **map;
    int i;
    int j;

    // 不要
    map = parser->map_buf;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j] != '\n')
        {
            printf("search player: %d %d %c\n", i, j, map[i][j]);

            //==FOUND
            if (ft_strchr(MAP_ORIENT_CHAR, map[i][j]))
            {
                *y = i;
                *x = j;
                return;
            }
            j++;
        }
        i++;
    }
    *x = -1;
    *y = -1;
    return;
}

int check_map_surrounded_with_floodfill(t_parser *parser, t_cub3d *env)
{
    int x;
    int y;
    int i;
    bool **filled_map;
    bool is_surrounded;

    (void)env;
    is_surrounded = true;

    set_player_position(parser, &x, &y);

    filled_map = ft_calloc(parser->map_max_y + 1, sizeof(bool *));
    if (!filled_map)
        return (-1);
    i = 0;
    while (i < parser->map_max_y)
    {
        filled_map[i] = ft_calloc(parser->map_max_x, sizeof(bool));
        if (!filled_map[i])
        {
            // free
            free_ptrarr((void **)filled_map);

            // put err
            return (update_err_flag(parser, ERR_MP_BORDERS));
        }
        i++;
    }
    // floodfill
    is_surrounded = floodfill(parser, filled_map, y, x);
    // free filled map
    free_ptrarr((void **)filled_map);
    if (!is_surrounded)
        //error check
        return (1);

    return (0);
}

int add_map_to_env(t_parser *parser, t_cub3d *env)
{
    int i;
    int((*check_map[4])(t_parser * parser, t_cub3d * env));
    check_map[0] = &check_player;
    check_map[1] = &check_cutted_map;
    // 順番逆？
    check_map[2] = &cpy_map_to_env;
    // check_map[3] = &check_if_open_map;
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
        printf("%d\n", i);
    }
    printf("after\n");
    update_player_position(env, parser->map_buf);
    return (0);
}
