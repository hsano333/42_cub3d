/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:39:54 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 12:12:26 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cub3d.h"
# include <math.h>

t_map_obj	get_cur_map_obj(t_cub3d *cub3d);
t_wpoint	get_dist_player_from_wall(t_cub3d *cub3d, t_point map \
							, double angle);
#endif
