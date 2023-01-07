/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:00:34 by hsano             #+#    #+#             */
/*   Updated: 2023/01/07 23:47:34 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

int		expose_win_hook(void *p);
int		hook_mouse_hook(int key, int x, int y, void *cub3d);
void	init_mlx_hook(t_cub3d *cub3d);
#endif
