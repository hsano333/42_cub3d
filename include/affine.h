/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:46:03 by hsano             #+#    #+#             */
/*   Updated: 2022/12/16 07:37:05 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFFINE_H
# define AFFINE_H
# include "cub3d.h"
# include <math.h>

void	affine(t_cub3d *cub3d, t_image *src_img, t_matrix matrix);
#endif
