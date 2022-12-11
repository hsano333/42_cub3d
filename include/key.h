/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 08:46:36 by hsano             #+#    #+#             */
/*   Updated: 2022/12/11 09:00:42 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
#define KEY_H

enum e_key {
	ARROW_LEFT = 65361,
	ARROW_UP = 65362,
	ARROW_RIGHT = 65363,
	ARROW_DOWN = 65364,
	ESC = 65307,
	A_KEY = 97,
	B_KEY = 98,
	C_KEY = 99,
	D_KEY = 100,
	E_KEY = 101,
	F_KEY = 102,
	G_KEY = 103,
	H_KEY = 104,
	I_KEY = 105,
	O_KEY = 111,
	P_KEY = 112,
	Q_KEY = 113,
	R_KEY = 114,
	S_KEY = 115,
	T_KEY = 116,
	U_KEY = 117,
	V_KEY = 118,
	W_KEY = 119,
	X_KEY = 120,
	Y_KEY = 121,
	Z_KEY = 122,
};

int	key_hook(int key, void *cub3d);
#endif
