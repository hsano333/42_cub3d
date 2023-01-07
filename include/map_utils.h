/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 08:12:59 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 01:23:19 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H
# include "cub3d.h"
# include <math.h>

t_point			add_map_point(t_point point, int x, int y);
t_point			get_point(int x, int y);
t_point			get_player_map_point(t_cub3d *cub3d);
int				is_collision_wall(t_cub3d *cub3d, t_ray *ray \
				, t_cub3d_type angle, t_point src_map);
t_cub3d_type	convert_positive_radian(t_cub3d_type radian);
#endif
