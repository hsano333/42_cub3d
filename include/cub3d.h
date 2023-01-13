/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoyagi <maoyagi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:18:21 by hsano             #+#    #+#             */
/*   Updated: 2023/01/13 20:43:57 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIN_WIDTH (800)
# define WIN_HEIGHT (600)
# define WALL_IMG_LEN (80)
# define WALL_LEN (400)
# define FOV (90)
# define MAP_SPACE (400)
# define MOVE_STEP (20)
# define ON_EXPOSE (14)
# define ON_DESTROY (17)
# define RATIO_Z (300)
# define BASE_ZX (400)
# define BASE_ZY (300)
# define CLOSE_DOOR_VALUE (90)
# define D_EQUAL 0.001
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

// ここはlinuxでやる
//  色情報
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}	t_color;

// マス
typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_const_angle
{
	double	degree;
	double	radian;
}	t_angle;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_wpoint {
	size_t	x;
	size_t	y;
	size_t	z;
}	t_wpoint;

typedef struct s_image
{
	int		bpp;
	int		sl;
	int		endian;
	int		height;
	int		width;
	void	*img;
	void	*addr;
}	t_image;

typedef struct s_wall_imgs
{
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
	t_image	*door;
	t_image	*enemy;
	t_image	*shot_enemy;
}	t_wall_imgs;

typedef enum e_map_obj
{
	EMPTY = 0,
	WALL = 1,
	SHOT,
	N_PLAYER,
	S_PLAYER,
	E_PLAYER,
	W_PLAYER,
	SPACE,
	DOOR,
	N_DOOR,
	S_DOOR,
	E_DOOR,
	W_DOOR,
}	t_map_obj;

typedef enum e_door_state
{
	OTHER = 0,
	OPEN,
	CLOSE,
	ANIME,
	SLOT,
	SLOT_RESULT,
}	t_door_state;

typedef struct s_map
{
	t_map_obj		obj;
	t_door_state	state;
}	t_map;

typedef enum e_wall_dir
{
	NORTH_WALL,
	SOUTH_WALL,
	EAST_WALL,
	WEST_WALL,
	NOT,
}	t_wall_dir;

typedef struct s_ray
{
	int			wall_pixel;
	int			is_door;
	int			shot_flag;
	double		begin_angle;
	double		last_angle;
	double		start_angle;
	double		stop_angle;
	t_point		map_point;
	t_point		begin_distance;
	t_point		last_distance;
	t_image		*wall_img;
	t_wall_dir	wall_dir;
}	t_ray;

typedef struct s_player
{
	size_t		world_x;
	size_t		world_y;
	t_point		shot;
	t_point		map;
	t_point		mass;
	t_angle		dir;
}	t_player;

typedef struct s_slot
{
	int			slot_flag;
	int			result_flag;
	int			release_count;
	t_point		map_point;
	t_wall_dir	shot_wall;
}	t_slot;

typedef struct s_cub3d
{
	int			door_change_flag;
	int			frame_count;
	int			lock;
	void		*mlx;
	void		*window;
	t_map		**map;
	t_ray		*ray;
	t_slot		slot;
	t_color		floor;
	t_color		ceiling;
	t_image		*image;
	t_angle		angles[WIN_WIDTH * 360 / FOV];
	t_player	*player;
	t_wall_imgs	*walls;
}	t_cub3d;

void	parse_map_main(t_cub3d *env, char **argv);
int		exit_game(t_cub3d *env);
#endif
