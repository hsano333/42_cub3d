/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 08:12:59 by hsano             #+#    #+#             */
/*   Updated: 2022/12/28 15:28:48 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H
# include "cub3d.h"
# include <math.h>

t_point	add_map_point(t_point point, int x, int y);
t_point	get_point(int x, int y);
t_point get_player_map_point(t_cub3d *cub3d);
t_point next_map_mass(t_cub3d_type angle, t_cub3d_type x_dist, t_cub3d_type y_dist, t_point map);
t_cub3d_type	convert_positive_radian(t_cub3d_type radian);

#endif
