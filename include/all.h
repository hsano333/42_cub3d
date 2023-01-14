/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_to_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:30:23 by maoyagi           #+#    #+#             */
/*   Updated: 2023/01/14 23:38:55 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ALL_H
# define ALL_H

# include "cub3d.h"
# include "cub3d_parser.h"

# include "../lib/libft/include/get_next_line.h"
# include "../lib/libft/include/libft_isto.h"
# include "../lib/libft/include/libft_mem.h"
# include "../lib/libft/include/libft_put.h"
# include "../lib/libft/include/libft_sort.h"
# include "../lib/libft/include/libft_str.h"
# include "../lib/libft/include/parse.h"

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "cub3d_parser.h"

# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

bool	ft_atoi_custom(long long *result, const char *str);

/************** exit	*****************/
int		exit_game(t_cub3d *env);
void	parse_map_exit(t_parser *parser);
void	add_to_env_exit(t_parser *parser, t_cub3d *env);

/************** free	*****************/
void	*c3d_free(void *ptr);
void	free_array_of_char_pointers(char *array[]);
void	free_array_of_int_pointers(int *array[]);
void	free_pointers_from_char_array(char *array[]);
void	free_pointers_from_int_array(int *array[]);

/************** parsing	*****************/
void	parse_map_main(t_cub3d *env, char **argv);
void	print_parse_err_exit(t_parser *parser, t_cub3d *env);
void	print_file_err_exit(int err);
int		check_file(char **av, int *fd, t_parser *parser);
int		fill_parser_buf(t_parser *parser, int fd);
int		check_type(char *line, int *type);
void	parse_line(t_parser *parser, char *line);
int		add_in_err_buf(t_parser *parser, int error_type);
int		add_to_env(t_parser *parser, t_cub3d *env);
int		add_color_to_env(t_parser *parser, t_cub3d *env);
int		add_map_to_env(t_parser *parser, t_cub3d *env);
int		update_player_position(t_cub3d *env, char **map);
int		cpy_map_to_env(t_parser *parser, t_cub3d *env);
char	**freetab_index(char **tab, int index, int opt);
int		update_err_flag(t_parser *parser, int err_nbr);
int		add_info_err_buf(t_parser *parser, int type, int error_num);
void	putstr_err(const char *err_type, const char *err_message);

void	free_ptrarr(void **ptr);
int		check_player(t_parser *parser, t_cub3d *env);
int		check_cutted_map(t_parser *parser, t_cub3d *env);
#endif
