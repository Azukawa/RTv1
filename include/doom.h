/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:19 by eniini            #+#    #+#             */
/*   Updated: 2022/01/31 22:20:12 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

//c lib
# include <string.h> //for sterror
# include <errno.h> //for errno macro
# include <unistd.h> //for write TBD
//SDL
# include "../libSDL2/include/SDL2/SDL_mixer.h"
# include "../libSDL2/include/SDL2/SDL.h"
//libft
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_gfx.h"
//doom
# include "defines.h"
# include "m_utils.h"

# define SPHERE		1
# define CYLINDER	2
# define CONE		3
# define PLANE		4
# define LIGHT		5

/*
*	shapes:
*		1 - sphere
*		2 - cylinder
*		3 - cone
*		4 - plane
*		5 - light (?)
*/
//generic datatype for 3d primitives
typedef struct s_obj {
	int			shape;
	t_vector	pos;
	t_vector	dir;
	float		r;
}				t_obj;

typedef struct s_cam {
	float		view_h;
	float		view_w;
	float		focal_l;
	t_vector	orig;
	t_vector	h;
	t_vector	v;
	t_vector	llc;
}				t_cam;

typedef struct s_ray {
	t_vector	orig;
	t_vector	dir;
}				t_ray;

//generated content
typedef struct s_world {
	t_mat4		m_proj;
	t_vector	camera;
	int			tricount;
	t_vector	cube_rotation;
	float		cam_distance;
	float		cam_fov;
}				t_world;

//Holds everything related directly to SDL's drawbuffer.
typedef struct s_rend
{
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	t_buffer		*rt_buffer;
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;

//superstruct that holds all the subsystem structs.
typedef struct s_doom {
	t_rend		rend;
	t_world		world;
	t_cam		cam;
	t_obj		*object;
	uint		objcount;
}				t_doom;

uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);

void		init_tests(t_doom *doom);
void		dotests(t_doom *doom);
void		cleanup_tests(t_doom *doom);

void		rt_render(t_doom *doom);
void		rt_init_cam(t_cam *cam, float fov, float ar);

#endif
