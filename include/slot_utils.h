/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:00:27 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 21:10:00 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLOT_UTILS_H
# define SLOT_UTILS_H
# include "slot_utils.h"
# include "cub3d.h"

void	set_on_slot(t_cub3d *cub3d, t_ray *ray, t_map door_p);
void	set_off_slot(t_cub3d *cub3d, t_ray *ray, t_map door_p);
#endif
