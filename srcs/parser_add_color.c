/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:31:17 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:31:17 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

int convert_rgb_to_int(t_color color)
{
    int val;

    val = 0;
    val = color.r;
    val = (val << 8) + color.g;
    val = (val << 8) + color.b;
    return (val);
}

void send_color_to_env(long long rgb[3], t_cub3d *env, int type)
{
    if (type == TYPE_F)
    {
        env->floor.r = (int)rgb[0];
        env->floor.g = (int)rgb[1];
        env->floor.b = (int)rgb[2];
        env->floor.color = convert_rgb_to_int(env->floor);
    }
    else
    {
        env->ceiling.r = (int)rgb[0];
        env->ceiling.g = (int)rgb[1];
        env->ceiling.b = (int)rgb[2];
        env->ceiling.color = convert_rgb_to_int(env->ceiling);
    }
}

int conv_and_add_to_env(t_parser *parser, t_cub3d *env, int type)
{
    long long rgb[3];
    int rgb_index;
    int info_index;
    char *buf;

    rgb_index = -1;
    info_index = 0;
    buf = &(parser->info_buf[type][info_index]);
    ft_memset(&rgb, 0, sizeof(rgb));
    if (ft_strlen(buf) > 11)
        return (add_info_err_buf(parser, type, ERR_FC_OVERFLOW));
    while (++rgb_index < 3)
    {
        // overflow check
        ft_atoi_custom(&(rgb[rgb_index]), buf);
        if (rgb[rgb_index] > 255)
            return (add_info_err_buf(parser, type, ERR_FC_FORM));
        while (ft_isdigit(*buf))
            buf++;
        buf++;
    }

    send_color_to_env(rgb, env, type);
    return (0);
}

int recheck_color_form(t_parser *parser, char *color, int type)
{
    int num_flag;

    num_flag = 3;
    while (*color)
    {
        if (ft_isdigit(*color))
            num_flag--;
        while (*color && ft_isdigit(*color))
            color++;
        if (*color == ',')
            color++;
    }
    if (num_flag)
        add_info_err_buf(parser, type, ERR_FC_FORM);
    return (num_flag);
}

int add_color_to_env(t_parser *parser, t_cub3d *env)
{
    int ret;

    ret = 0;
    ret += recheck_color_form(parser, parser->info_buf[TYPE_F], TYPE_F);
    ret += recheck_color_form(parser, parser->info_buf[TYPE_C], TYPE_C);

    if (!ret)
    {
        ret += conv_and_add_to_env(parser, env, TYPE_F);
        ret += conv_and_add_to_env(parser, env, TYPE_C);
    }
    return (ret);
}