/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_to_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:30:23 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:30:23 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

// おかしい行の文字列と行番号を追加
int add_info_err_buf(t_parser *parser, int type, int error_num)
{
    // ブロッキングエラー？
    //  bitを立てる
    parser->blocking_err_flag |= (1 << error_num);
    if (type <= TYPE_C)
        parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->info_buf_line[type];
    else
        parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->gnl_cnt;
    parser->err_buf[parser->err_buf_index][ERROR_CODE] = error_num;
    parser->err_buf_index++;
    return (-1);
}

/*
int load_texture(t_c3d *env, t_mlx *mlx, int i, t_img *img)
{
    int *tex;
    char *path;
    int x;
    int y;

    tex = env->textures[i];
    path = env->tex_paths[i];
    img->mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img->x, &img->y);
    if (!img->mlx_img)
        return (-1);
    img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
    y = 0;
    while (y < img->y)
    {
        x = 0;
        while (x < img->x)
        {
            tex[img->x * y + x] = img->addr[img->x * y + x];
            ++x;
        }
        ++y;
    }
    return (0);
}

int load_textures(t_c3d *env, t_mlx *mlx)
{
    t_img img[_TEX_NBR];
    int i;
    int j;

    i = -1;
    j = 0;
    while (++i < _TEX_NBR)
    {
        if (load_texture(env, mlx, i, &img[i]))
            break;
    }
    while (j < i)
    {
        mlx_destroy_image(mlx->mlx_ptr, img[j].mlx_img);
        j++;
    }
    if (i != _TEX_NBR)
        return (-1);
    return (0);
}

int add_path_to_env(t_parser *parser, t_c3d *env)
{
    int i;
    int load_test_ret;

    i = -1;
    while (++i < _TEX_NBR)
        env->tex_paths[i] = parser->info_buf[i];
    load_test_ret = load_textures(env, &(env->mlx));
    if (load_test_ret)
        return (add_info_err_buf(parser, load_test_ret, ERR_TX_PATH));
    return (0);
}
*/

// t_envにする
int add_to_env(t_parser *parser, t_cub3d *env)
{

    // テストではmlxはやらない
    /*

    int i;
    int((*add_to_env[3])(t_parser * parser, t_c3d * env));
    add_to_env[0] = &c3d_add_path_to_env;
    add_to_env[1] = &c3d_add_color_to_env;
    add_to_env[2] = &c3d_add_map_to_env;
    i = -1;
    while (++i < 3)
    {
        if (add_to_env[i](parser, env))
            return (parser->blocking_err_flag);
    }
    */

    int i;
    int((*add_to_env[2])(t_parser * parser, t_cub3d * env));

    add_to_env[0] = &add_color_to_env;
    add_to_env[1] = &add_map_to_env;
    i = -1;
    while (++i < 2)
    {
        if (add_to_env[i](parser, env))
            return (parser->blocking_err_flag);
    }
    return (0);
}