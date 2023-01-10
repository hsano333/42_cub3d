/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 12:17:51 by hsano             #+#    #+#             */
/*   Updated: 2023/01/10 21:06:43 by maoyagi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "cub3d.h"
#include "wall.h"
#include "mlx.h"
#include "mlx_int.h"
#include "window.h"
#include "close.h"

int main(int argc, char **argv)
{
	t_cub3d *cub3d;

	cub3d = init(argc, argv);
	if (!cub3d)
		exit(1);
	mlx_loop(cub3d->mlx);
	close_cub3d(cub3d);
	exit_game(cub3d);
}
