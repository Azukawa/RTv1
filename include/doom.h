/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:19 by eniini            #+#    #+#             */
/*   Updated: 2022/01/14 14:58:09 by eniini           ###   ########.fr       */
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

//generated content
typedef struct s_world {
	//t_tri		*cube;
	t_quad		*cube;
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
	int				win_pixel_pitch;
	t_bool			run;
}					t_rend;

//Keyevent handling.
typedef struct s_keys {
	t_bool		up_pressed;
	t_bool		down_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_bool		fps_switch;
	t_bool		mouse_switch;
	t_bool		rot_switch;
}				t_keys;
//superstruct that holds all the subsystem structs.
typedef struct s_doom {
	t_rend		rend;
	t_world		world;
	t_vector	mouse;
	t_keys		keys;
	int			global_fps;
	double		delta;
	int			cur_sec;
}				t_doom;

uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p);

void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_line(t_buffer *buf, t_pixel p0, t_pixel p1, uint32_t color);

void		draw_circle(t_buffer *buf, t_pixel p, int r, uint32_t color);
void		draw_filled_circle(t_buffer *buf, t_pixel p, int r, uint32_t col);
void		draw_square(t_pixel start, t_pixel end, t_buffer *buf, uint32_t c);
void		draw_vector_line(t_buffer *buf, t_line line, uint32_t c);

void		r_dotests(t_doom *doom);
void		draw_cube(t_doom *doom);

void		init_tests(t_doom *doom);
void		dotests(t_doom *doom);
void		cleanup_tests(t_doom *doom);

void		keyevent(t_doom *doom, SDL_Event *e);
void		fps_counter(int *global_fps);
void		mouse_movement(t_doom *doom);

t_quad		*init_cube(void);
void		set_cube(t_quad *c, t_fvec3 d, t_fvec3 p);
#endif
