/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:52:37 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 23:48:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANGLE_UTILS_H
# define ANGLE_UTILS_H
# include <math.h>
# include "cub3d.h"

typedef enum e_rotate_mode
{
	RORATE_PLUS,
	RORATE_MINUS,
}	t_rotate_mode;

t_cub3d_type	distance_to_angle(t_cub3d_type val \
				, t_cub3d_type angle, t_rotate_mode mode);
int				is_in_range_fov(t_cub3d *cub3d, t_cub3d_type angle);
#endif
