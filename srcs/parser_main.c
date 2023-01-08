/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:02:56 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:02:56 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

void print_parser(t_parser parser)
{
    printf("type: %d\n", parser.type);
    printf("line: %s\n", parser.line);
    printf("gnlcnt: %d\n", parser.gnl_cnt);
    printf("mp_max_x: %d\n", parser.map_max_x);
    printf("mp_max_y: %d\n", parser.map_max_y);
    printf("info_flag: %d\n", parser.info_buf_flag);
    printf("blocking_flag: %d\n", parser.blocking_err_flag);
    printf("map_index: %d\n", parser.map_buf_index);
    for (size_t i = 0; i < 6; i++)
    {
        printf("info_buf: %s\n", parser.info_buf[i]);
        printf("info_buf_line: %d\n", parser.info_buf_line[i]);
    }
    for (size_t i = 0; parser.map_buf[i]; i++)
    {
        printf("map: %d %s\n", parser.map_line_buf[i], parser.map_buf[i]);
    }
    /*
    for (size_t i = 0; parser.err_buf[i][0]; i++)
    {
        printf("err_buf: %s\n", parser.err_buf[i][0]);
        printf("err_buf: %s\n", parser.err_buf[i][1]);
    }
    */
}

void print_env(t_cub3d *env)
{
    // map
    /*
    printf("MAP\n");
    for (size_t i = 0; env->map2[i]; i++)
    {
        printf("%zu: \t %s\n", i, env->map2[i]);
    }
    */
    // 2重ループにする
    for (size_t i = 0; env->map[i]; i++)
    {
        for (size_t j = 0; env->map[i][j].obj != 100; j++)
        {
            printf("%d",env->map[i][j].obj);
        }
        printf("\n");
    }


    // textures

    // path
    /*
    printf("PATHs\n");
    for (size_t i = 0; i < _TEX_NBR; i++)
    {
        printf("%s\n", env->tex_paths[i]);
    }
    */

    // player
    /*
    printf("PLAYER\n");
    printf("player: dirx: %f, diry: %f\n", env->player.dir.x, env->player.dir.y);
    printf("player speed: %f\n", env->player.speed);
    printf("player move: %d\n", env->player.move);
    printf("player posx: %f, posy: %f\n", env->player.pos.x, env->player.pos.y);
    printf("player cam_planex: %f, cam_planey: %f\n", env->player.cam_plane.x, env->player.cam_plane.y);
    */

    // floor
    printf("COLOR FLOOR\n");
    printf("color: %x\n", env->floor.color);
    printf("r: %d, g: %d, b: %d\n", env->floor.r, env->floor.g, env->floor.b);

    // celing
    printf("COLOR CELLING\n");
    printf("color: %x\n", env->ceiling.color);
    printf("r: %d, g: %d, b: %d\n", env->ceiling.r, env->ceiling.g, env->ceiling.b);
}

int update_err_flag(t_parser *parser, int err_nbr)
{
    parser->blocking_err_flag |= (1 << err_nbr);
    return (parser->blocking_err_flag);
}

char **freetab_index(char **tab, int index, int opt)
{
    int i;
    i = -1;
    if (opt)
    {
        while (++i < index)
        {
            free(tab[i]);
            tab[i] = NULL;
        }
    }
    else
    {
        while (tab[++i])
        {
            free(tab[i]);
            tab[i] = NULL;
        }
        free(tab);
    }
    return (NULL);
}

void parse_map_main(t_cub3d *env, char **argv)
{
    int fd;
    t_parser parser;

    fd = -1;
    ft_memset(&parser, 0, sizeof(t_parser));
    if (check_file(argv + 1, &fd, &parser))
        // c3d_print_file_err_exit(parser.blocking_err_flag);
        printf("Error");

    else if (fill_parser_buf(&parser, fd))
        print_parse_err_exit(&parser, env);

    // print parser
    print_parser(parser);

    /*
    else if (c3d_init(env))
        c3d_add_to_env_exit(&parser, env);
    */

    // cpy
    if (add_to_env(&parser, env))
        print_parse_err_exit(&parser, env);

    // print env
    print_env(env);

    // free
    // index付きで解放
    freetab_index(parser.map_buf, parser.map_buf_index, WITH_INDEX);
}
