/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projective_trans.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 07:32:09 by hsano             #+#    #+#             */
/*   Updated: 2022/12/17 09:30:53 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTIVE_TRANS_H
# define PROJECTIVE_TRANS_H
# include "cub3d.h"
# include "math.h"

void	projective_trans(t_cub3d *cub3d, t_image *src_img, t_matrix *matrix, t_xyz *src_xyz, t_xyz *dst_xyz, t_xspace *x_space);
#endif

