/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:14:34 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 07:12:30 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLOT_H
# define SLOT_H
# include "cub3d.h"
# include <stdbool.h>

int	is_raise_shot_flag(t_cub3d *cub3d, t_ray *ray,  int start, int end);
int	count_frame(t_cub3d *cub3d);
void	change_image(t_cub3d *cub3d, t_ray *ray, t_point next);
void	slot_flag(t_cub3d *cub3d, t_ray *ray);
void	manage_slot_flag(t_cub3d *cub3d, t_ray *ray, int y);
#endif
