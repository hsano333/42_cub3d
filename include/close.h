/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:11:44 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 08:27:07 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H
# include "cub3d.h"

void	clear_map(t_cub3d *cub3d);
void	clear_cub3d(t_cub3d *cub3d);
void	error_and_end_game(t_cub3d *cub3d, char *str);
int	close_cub3d(t_cub3d *cub3d);
#endif

