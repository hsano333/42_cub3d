/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_texture_mapping.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:54:00 by hsano             #+#    #+#             */
/*   Updated: 2023/01/08 02:36:33 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_TEXTURE_MAPPING_H
# define CALC_TEXTURE_MAPPING_H
# include <math.h>
# include "cub3d.h"

void	calc_texture_mapping(t_cub3d *cub3d, int x, t_ray *ray, double angle);
#endif
