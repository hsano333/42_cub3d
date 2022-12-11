/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:50:01 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 12:04:08 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mouse.h"
#include "cub3d.h"
#include "libft_mem.h"
#include "libft_str.h"

int	hook_mouse_hook(int key, int x, int y, void *cub3d_v)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_v;
	cub3d = (t_cub3d *)cub3d;
	key = (int)key;
	printf("mouse move:x=%d, y=%d\n", x, y);
	return (true);
}
