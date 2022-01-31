/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:13 by eniini            #+#    #+#             */
/*   Updated: 2022/01/31 22:09:43 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdint.h>

//WINDOW
# define WIN_W	1920
# define WIN_H	1080

# define WIN_NAME	"RTv1 build version 0.1"
//COLOR PALETTE
# define C_OCHRE	0xffbc8650
# define C_BRICK	0xffbc5050
# define C_LEMON	0xffbcbc50
# define C_LIME		0xff86bc50
# define C_GRASS	0xff50bc50
# define C_MINT		0xff50bc86
# define C_ICE		0xff50bcb7
# define C_SKY		0xff508bbc
# define C_AZURE	0xff5055bc
# define C_GRAPE	0xff8150bc
# define C_CHERRY	0xffbc5080
# define C_PLUM		0xffFF5733
# define C_BLUE		0xff0000ff
# define C_GREEN	0xff00ff00
# define C_RED		0xffff0000
# define C_TEAL		0xff00fbff
# define C_GREY		0xff949494
# define C_BLACK	0xff000000
# define C_WHITE	0xffffffff
# define C_GRAY		0xff808080
# define C_PINK		0xffe297df
# define C_PURPLE	0xff6e26b4
# define C_ORANGE	0xffe7973d
# define C_DEBUG	0xff26ff26

typedef struct s_vector {
	float	x;
	float	y;
	float	z;
	float	w;
}			t_vector;
typedef t_vector	t_vertex;

//4 x 4 matrix
typedef struct s_mat4 {
	float	m[4][4];
}			t_mat4;

//Datatype to store an ARBG image data. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_buffer {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

#endif
