/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:25:28 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/07 21:25:28 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/all.h"

char *skip_useless_char(char *line, int type, int opt)
{
    if (opt == 0)
    {
        while (*line == ' ')
            line++;
        if (type <= TYPE_EA)
            line += 3;
        else
            line += 2;
        while (*line == ' ')
            line++;
    }
    else
    {
        while (*line == ' ')
            line++;
        while (*line == '0')
        {
            line++;
            if (!(*line >= '0' && *line <= '9') && line--)
                break;
        }
    }
    return (line);
}

void parse_texture(t_parser *parser, char *line, int type)
{
    int i;

    if (!(parser->info_buf_flag & (1 << type)))
    {
        i = -1;
        while (line[++i] && !ft_strchr(" \n", line[i]))
        {
            parser->info_buf[type][i] = line[i];
            if (i == MAX_PATH_LENGH && add_in_err_buf(parser, ERR_TX_PATH_LENGH))
                break;
        }
        parser->info_buf[type][i] = '\0';
        parser->info_buf_flag |= (1 << type);
        parser->info_buf_line[type] = parser->gnl_cnt;
    }
    else
        add_in_err_buf(parser, ERR_TX_MULTIDEF);
}

void parse_color(t_parser *parser, char *line, int type)
{
    int i;

    if (!(parser->info_buf_flag & (1 << type)))
    {
        i = 0;
        while (*line && *line != '\n')
        {
            while ('0' <= *line && *line <= '9')
                parser->info_buf[type][i++] = (*line++);
            if (*line == ',')
                parser->info_buf[type][i++] = *(line++);
            if (!ft_isdigit(*line) && *line != '\n')
            {
                add_in_err_buf(parser, ERR_FC_FORM);
                break;
            }
        }
        parser->info_buf[type][i] = '\0';
        printf("parser_line: %s\n", parser->info_buf[type]);
        parser->info_buf_flag |= (1 << type);
        parser->info_buf_line[type] = parser->gnl_cnt;
    }
    else
        add_in_err_buf(parser, ERR_FC_MULTIDEF);
}

void parse_map(t_parser *parser, char *line, int type)
{
    int line_len;

    (void)type;
    if (parser->map_buf_index < PARSER_BUFFER_SIZE - 1)
    {
        line_len = ft_strlen(line);
        // line_len = c3d_strlen(line) - 1;
        //   行をコピー
        parser->map_buf[parser->map_buf_index] = line;
        // 行番号
        parser->map_line_buf[parser->map_buf_index] = parser->gnl_cnt;
        parser->map_buf_index++;
        if (line_len > parser->map_max_x)
            parser->map_max_x = line_len;
        parser->map_max_y++;

        // マップ大きさを確認
        if (line_len >= MAP_MAX_LENGH || parser->map_max_y >= MAP_MAX_HEIGHT)
            add_in_err_buf(parser, ERR_MP_TOO_BIG);
    }
    else
        add_in_err_buf(parser, ERR_MP_TOO_BIG);
}

// 行を解析
void parse_line(t_parser *parser, char *line)
{
    void((*parse_line[7])(t_parser * parser, char *line, int type));
    parse_line[TYPE_NO] = &parse_texture;
    parse_line[TYPE_SO] = &parse_texture;
    parse_line[TYPE_WE] = &parse_texture;
    parse_line[TYPE_EA] = &parse_texture;
    // 色情報
    parse_line[TYPE_F] = &parse_color;
    parse_line[TYPE_C] = &parse_color;
    // map読み込み
    parse_line[TYPE_MAP] = &parse_map;
    if (parser->type <= TYPE_C)
        line = skip_useless_char(line, parser->type, 0);

    if (parser->type == TYPE_ERR)
        add_in_err_buf(parser, ERR_GIBBER);
    else
        parse_line[parser->type](parser, line, parser->type);

    if (parser->type != TYPE_MAP && parser->line)
        free(parser->line);
}