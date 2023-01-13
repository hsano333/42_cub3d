/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:52:37 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 21:16:24 by hsano            ###   ########.fr       */
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

double	distance_to_angle(double val \
				, double angle, t_rotate_mode mode);
int		is_in_range_fov(t_cub3d *cub3d, double angle);
double	fit_in_radian(double angle);
int		is_exceed_angle(t_ray *ray, double angle);
#endif
