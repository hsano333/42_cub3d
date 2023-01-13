/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:13:47 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 08:24:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

int	update_image_per_wall(t_cub3d *cub3d, t_ray *ray, int offset);
int	update_image(t_cub3d *cub3d);
#endif
