/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:33:19 by hsano             #+#    #+#             */
/*   Updated: 2022/12/20 07:43:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "cub3d.h"
# include <math.h>

int	fire_ray(t_cub3d *cub3d, size_t i, t_cub3d_type angle);
#endif
