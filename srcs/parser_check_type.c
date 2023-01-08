/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:20:55 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:20:55 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

static int is_type_null(char *line, int *type)
{
    if (!line)
    {
        *type = TYPE_EOF;
        return (1);
    }
    return (0);
}

static int is_type_useless(char *line, int *type)
{
    if (*line == '\n')
    {
        *type = TYPE_USELESS;
        return (1);
    }
    return (0);
}

static int is_type_key(char *line, int *type)
{
    const char *key_tab[] = {
        [TYPE_NO] = "NO ",
        [TYPE_SO] = "SO ",
        [TYPE_WE] = "WE ",
        [TYPE_EA] = "EA ",
        [TYPE_F] = "F ",
        [TYPE_C] = "C ",
    };

    while ((*type) < TYPE_MAP)
    {
        if (ft_strncmp(key_tab[*type], line, ft_strlen((char *)key_tab[*type])) == 0)
            return (1);
        (*type)++;
    }
    return (0);
}

static int is_type_map(char *line, int *type)
{
    while (*line != '\n')
    {
        if (!ft_strchr(MAP_CHAR, *line))
        {
            *type = TYPE_ERR;
            break;
        }
        line++;
    }

    if (*type != TYPE_ERR)
        *type = TYPE_MAP;
    return (*type);
}

int check_type(char *line, int *type)
{
    int i;
    int((*check_type[4])(char *line, int *type));

    check_type[0] = &is_type_null;
    check_type[1] = &is_type_useless;
    check_type[2] = &is_type_key;
    check_type[3] = &is_type_map;
    i = 0;
    *type = 0;
    if (line)
        while (*line == ' ')
            line++;
    while (i < 4)
        if (check_type[i++](line, type))
            break;
    return (*type);
}