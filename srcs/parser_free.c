/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:05:14 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 23:05:14 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

void *c3d_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
    return (NULL);
}

void free_array_of_char_pointers(char *array[])
{
    size_t i;

    i = 0;
    while (array[i])
    {
        c3d_free(array[i]);
        ++i;
    }
    array = c3d_free(array);
}

void free_array_of_int_pointers(int *array[])
{
    size_t i;

    i = 0;
    while (array[i])
    {
        c3d_free(array[i]);
        i++;
    }
    array = c3d_free(array);
}

void free_pointers_from_char_array(char *array[])
{
    size_t i;

    i = 0;
    while (array[i] && i < _TEX_NBR)
    {
        c3d_free(array[i]);
        ++i;
    }
}

void free_pointers_from_int_array(int *array[])
{
    size_t i;

    i = 0;
    while (array[i] && i < _TEX_NBR)
    {
        c3d_free(array[i]);
        ++i;
    }
}