/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 08:16:41 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 23:40:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include "cub3d.h"

t_image	*load_wall_img(t_cub3d *cub3d, char *path);
#endif
