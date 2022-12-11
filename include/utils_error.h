/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 07:45:47 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 07:47:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ERROR_H
# define UTILS_ERROR_H
# include "cub3d.h"

void	clear_map(t_cub3d *cub3d);
void	clear_cub3d(t_cub3d *cub3d);
void	error_and_end_game(t_cub3d *cub3d, char *str);
#endif
