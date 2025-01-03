/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:02:17 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 20:19:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_H
# define RAY_UTILS_H
# include "cub3d.h"

t_point	search_wall(t_cub3d *cub3d \
			, t_ray *ray, double angle, t_point map);
int		is_collision_wall(t_cub3d *cub3d, t_ray *ray \
						, double angle, t_point src_map);
typedef struct s_distance {
	double	x;
	double	y;
}	t_distance;

#endif
