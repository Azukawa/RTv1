/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:13 by eniini            #+#    #+#             */
/*   Updated: 2022/01/14 18:39:06 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TRICOUNT_SPHERE	20
# define QUADCOUNT_CUBE		6

# include <stdint.h>

//WINDOW
# define WIN_W	800
# define WIN_H	600
# define WIN_HW	400
# define WIN_HH	300
# define WIN_NAME	"RTv1 build version 0.0"
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
# define C_BLUE		0XFF0000FF
# define C_GREEN	0XFF00FF00
# define C_RED		0XFFFF0000
# define C_TEAL		0XFF00FBFF
# define C_GREY		0XFF949494
# define C_BLACK	0xFF000000
# define C_WHITE	0xFFFFFFFF
# define C_GRAY		0xFF808080
# define C_PINK		0xFFE297DF
# define C_PURPLE	0xFF6E26B4
# define C_ORANGE	0xFFE7973D
# define C_DEBUG	0xFF26FF26

/*
*	Defines a bunch of generic/specialized datatypes for use within multiple
*	areas of the program.
*/

typedef struct s_vector {
	float	x;
	float	y;
	float	z;
	float	w;
}			t_vector;
typedef t_vector	t_vertex;

typedef struct s_fvector {
	float	x;
	float	y;
	float	z;
}			t_fvector;
typedef t_fvector	t_fvec3;

//base unit for 3d projection
typedef struct s_tri {
	t_vector	p[3];
}				t_tri;

typedef struct s_quad {
	t_vector	p[4];
}				t_quad;

//4 x 4 matrix
typedef struct s_mat4 {
	float	m[4][4];
}			t_mat4;
//screenspace unit. Essentially a pixel coordinate w/ color information
typedef struct s_point {
	int			x;
	int			y;
	uint32_t	c;
}				t_point;
//screenspace floating-point unit. Pixel coordinate + color
typedef struct s_fpoint {
	float		x;
	float		y;
	uint32_t	c;
}				t_fpoint;

typedef struct s_pixel {
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_square {
	t_pixel	start;
	t_pixel	end;
}			t_square;

typedef struct s_ivec3 {
	int			x;
	int			y;
	int			z;
}				t_ivec3;
//integer-based line drawing stuct
typedef struct s_line {
	t_ivec3		start;
	t_ivec3		end;
	uint32_t	color;
}				t_line;
//Handles mapping signed/unsigned ints into a range.
typedef struct s_range {
	long	start;
	long	end;
}			t_range;
//Datatype to store an ARBG image. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_img {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_img;
typedef t_img		t_buffer;

#endif
