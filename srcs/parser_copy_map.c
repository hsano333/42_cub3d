/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_copy_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:33:24 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:33:24 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"
#include "../include/close.h"

static void free_ptrarr(void **ptr)
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

t_map **init_env_map(t_parser *parser)
{
    t_map **map;
    int i;

    i = -1;
    map = malloc(sizeof(t_map *) * parser->map_max_y + 1);
    if (map)
    {
        while (++i < parser->map_max_y)
        {
            map[i] = malloc(sizeof(t_map) * parser->map_max_x + 1);
            ft_memset(map[i], 0, parser->map_max_x); //+1?
            if (!map[i])
            {
                free_ptrarr((void **)map);
                break;
            }
        }
        map[i] = NULL;
    }
    return (map);
}

int get_map_obj_nbr(char c)
{
    int i;
    i = 0;
    while (MAP_OBJ_CHAR[i])
    {
        if (c == MAP_OBJ_CHAR[i])
            return (i);
        i++;
    }
    return (1);
}

t_map **map_cpy(t_parser *parser, t_map **env_map)
{
    char *to_cpy;
    t_map *dst;
    int i;
    t_map_obj obj_n;
    t_map m;

    i = -1;
    while (++i < parser->map_max_y)
    {
        to_cpy = parser->map_buf[i];
        dst = env_map[i];
        while (*to_cpy != '\n')
        {
            obj_n = (t_map_obj)get_map_obj_nbr(*to_cpy);
            m = (t_map){.obj = obj_n};
            *dst++ = m;
            to_cpy++;
        }
        *dst = (t_map){.obj = 100};
    }
    env_map[i] = NULL;
    return (env_map);
}

int cpy_map_to_env(t_parser *parser, t_cub3d *env)
{
    t_map **map;

    map = init_env_map(parser);
    if (!map)
        add_to_env_exit(parser, env);
    env->map = map_cpy(parser, map);
    if (!env->map)
        return (update_err_flag(parser, ERR_MP_UNABLE_TO_CPY));
    return (0);
}
