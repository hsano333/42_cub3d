/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:46:39 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 12:04:46 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key.h"
#include "close.h"
#include "stdio.h"


int	key_hook(int key, void *cub3d)
{
	if (((t_cub3d *)cub3d)->lock)
		return (false);
	if (key == ESC)
		close_cub3d(cub3d);
	else if (key == ARROW_LEFT)
		;
	else if (key == ARROW_RIGHT)
		;
	else if (key == ARROW_UP)
		;
	else if (key == ARROW_DOWN)
		;
	else if (key == W_KEY)
		;
	else if (key == A_KEY)
		;
	else if (key == S_KEY)
		;
	else if (key == D_KEY)
		;
	else
		printf("not defined key=%d\n", key);
	printf("press key=%d\n", key);
	return (true);
}
