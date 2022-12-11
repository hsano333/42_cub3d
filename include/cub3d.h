/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:18:21 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 09:03:51 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3d_H
# define CUB3d_H
# define WIN_WIDTH (800)
# define WIN_HEIGHT (600)
# define WALL_WIDTH (400)
# define WALL_HEIGHT (400)
# define FOV (120)
# define CAMERA (100)
# define MAP_SPACE (25)
# define ON_EXPOSE (14)
# define ON_DESTROY (17)
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>


typedef double t_cub3d_type;

typedef struct s_image
{
	int	bpp;
	int	sl;
	int	endian;
	int	height;
	int	width;
	void	*img;
	void	*addr;
}	t_image;

typedef struct s_wall_imgs
{
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
	t_image	*sprite;
}	t_wall_imgs;

typedef enum e_map_obj
{
	EMPTY = 0,
	WALL = 1,
	N_PLAYER,
	S_PLAYER,
	E_PLAYER,
	W_PLAYER,
	SPACE,
	N_DOOR,
	S_DOOR,
	E_DOOR,
	W_DOOR,
}	t_map_obj;

typedef enum e_door_state
{
	OPEN,
	CLOSE,
}	t_door_state;

typedef struct s_map
{
	t_map_obj	obj;
	t_door_state	state;
}	t_map;

typedef struct s_cub3d
{
	void		*mlx;
	void		*window;
	t_map		**map;
	t_image		*image;
	t_wall_imgs	*walls;
	int		lock;
}	t_cub3d;

typedef struct s_player
{
	int	map_x;
	int	map_y;
	int	x;
	int	y;
	int	world_x; // map_x * SPACE + x
	int	world_y; // map_y * SPACE + y
	int	dir;
}	t_player;

typedef struct s_door
{
	int	map_x;
	int	map_y;
	int	is_north;
	int	is_south;
	int	is_east;
	int	is_west;
	int	open_north;
	int	open_south;
	int	open_east;
	int	open_west;
}	t_door;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_matrix {
	t_cub3d_type	a;
	t_cub3d_type	b;
	t_cub3d_type	c;
	t_cub3d_type	d;
	t_cub3d_type	e;
	t_cub3d_type	f;
}	t_matrix;

typedef struct s_xyz {
	t_cub3d_type	x;
	t_cub3d_type	y;
	t_cub3d_type	z;
	t_cub3d_type	theta;
	t_cub3d_type	xz_ratio;
	t_cub3d_type	yz_ratio;
	t_cub3d_type	sin;
	t_cub3d_type	cos;
}	t_xyz;

#endif
