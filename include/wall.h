/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:16:41 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 11:11:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
#define WALL_H
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include "cub3d.h"

void	load_wall_img(t_cub3d *cub3d, void *mlx, t_image **wall, char *path);
#endif
