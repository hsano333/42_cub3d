/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:50 by hsano             #+#    #+#             */
/*   Updated: 2023/01/14 16:19:56 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "cub3d.h"
#include "wall.h"
#include "mlx.h"
#include "mlx_int.h"
#include "window.h"
#include "close.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = init(argc, argv);
	if (!cub3d)
		exit(1);
	mlx_loop(cub3d->mlx);
	close_cub3d(cub3d);
	exit_game(cub3d);
	return (true);
}
