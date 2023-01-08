/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:12:40 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:12:40 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

/*
static int find_last_c_occurence(char *path, char c)
{
    int i;
    int occurence;

    i = -1;
    occurence = i + 1;
    while (path[++i])
    {
        if (path[i] == c)
            occurence = i;
    }
    return (occurence);
}
*/

static int check_extention(char *file)
{
    // int dot;
    char *dot;
    char *tmp;
    int ret;

    ret = 0;
    if (file)
    {
        //.の位置 rchrで良いのでは
        // dot = c3d_find_last_c_occurence(file, '.');
        dot = ft_strrchr(file, '.');
        tmp = dot + 1;
        // cubかどうか
        if (dot == 0 || ft_strncmp(tmp, "cub", 4) != 0)
            // bitを立てる
            return (ret | (1 << ERR_EXTENTION));
        // printf("%s\n", tmp);

        return (0);
    }
    return (ret | 1 << ERR_EXTENTION);
}

/*
static int c3d_check_if_folder(char *file)
{
    int fd;

    fd = open(file, O_DIRECTORY);
    if (fd != -1)
    {
        close(fd);
        return (1 << ERR_FOLDER);
    }
    return (0);
}
*/

int check_file(char **av, int *fd, t_parser *parser)
{
    // printf("%s\n", av[0]);
    if (*av)
    {
        parser->blocking_err_flag += check_extention(av[0]);
        // parser->blocking_err_flag += c3d_check_if_folder(av[0]);
        *fd = open(av[0], O_RDONLY);
        // printf("%d\n", *fd);
        //  エラーの場合
        if (*fd == -1 && !parser->blocking_err_flag)
        {
            //==?
            if (errno == EACCES)
                // if ((errno ^ EACCES) == 0)
                parser->blocking_err_flag |= (1 << ERR_CHMOD);
            else if (errno == EACCES)
                // else if ((errno ^ ENOENT) == 0)
                parser->blocking_err_flag |= (1 << ERR_PATH);
            else
            {
                perror("cub3d");
                exit(errno);
            }
        }
        // printf("%d\n", parser->blocking_err_flag);
        // close(*fd);
    }
    else
        parser->blocking_err_flag |= (1 << ERR_NO_FILE);
    return (parser->blocking_err_flag);
}