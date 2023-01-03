/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 08:12:59 by hsano             #+#    #+#             */
/*   Updated: 2023/01/03 16:48:16 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H
# include "cub3d.h"
# include <math.h>

t_point	add_map_point(t_point point, int x, int y);
t_point	get_point(int x, int y);
t_point get_player_map_point(t_cub3d *cub3d);
//t_point next_map_mass(t_cub3d_type angle, t_cub3d_type x_dist, t_cub3d_type y_dist, t_point map);
t_point next_map_mass(t_cub3d_type angle, t_point point, t_point map);
t_cub3d_type	convert_positive_radian(t_cub3d_type radian);
t_point	get_wall_distance_from_player(t_cub3d *cub3d, t_point map_point, t_point offset);

#endif
