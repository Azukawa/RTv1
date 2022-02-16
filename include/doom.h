/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:19 by eniini            #+#    #+#             */
/*   Updated: 2022/02/16 12:50:33 by alero            ###   ########.fr       */
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

enum type {

	SPHERE,
	PLANE,
	CYL,
	CONE,
	LIGHT

};

typedef	struct	s_color{
	float red;
	float green;
	float blue;
}				t_color;


typedef struct	s_object{
	t_fvector	pos;
	t_fvector	dir;
	int			material;
	float		r;
	int			type;
	float		angle;
	t_color		intensity;
}				t_object;

typedef	struct	s_plane{
	t_fvector	pos;
	t_fvector	dir;
	int			material;
}				t_plane;

typedef struct	s_cylinder{
	t_fvector	pos;
	t_fvector	dir;
	float		r;
	int			material;
}				t_cylinder;

typedef struct	s_cone{
	t_fvector	pos;
	t_fvector	dir;
	float		r;
	float		angle;
}				t_cone;

typedef struct	s_ray{
	t_fvector	start;
	t_fvector	dir;
}				t_ray;

typedef struct	s_material{
	t_color	diffuse;
	float	reflection;
}				t_material;

typedef	struct s_sphere{
	t_fvector	pos;
	float		r;
	int			material;
}				t_sphere;


typedef struct s_light{
	t_color		intensity;
	t_fvector	pos;

}				t_light;

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
	t_keys		keys;
	int			global_fps;
	t_material	material[5];
	t_sphere	sphere[5];
	t_plane		plane[5];
	t_cylinder	cylinder[5];
	t_cone		cone[5];
	t_light		light[5];
	t_object	object[10];
	int			xvar;
	int			yvar;
	int			zvar;
	int			object_count;
}				t_doom;

uint32_t	color_lerp(uint32_t c1, uint32_t c2, double p);
void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		init_tests(t_doom *doom);
void		ales_rayc(t_doom *doom);
void		keyevent(t_doom *doom, SDL_Event *e);
t_fvector	v_cross(t_fvector va, t_fvector vb);
float		v_dot(t_fvector va, t_fvector vb);
float		v_len(t_fvector v);
t_fvector	v_normalize(t_fvector v);
t_fvector	v_add(t_fvector a, t_fvector b);
float		lerp1d(float a, float b, float t);
t_fvector	v_sub(t_fvector a, t_fvector b);
t_fvector	v_div(t_fvector vector, float c);
t_fvector	v_mult(t_fvector vector, float c);
uint32_t	get_color2(unsigned char r, unsigned char g, unsigned char b);
float		two_point_dist(t_fvector a, t_fvector b);
void		quadratic_equation(t_fvector abc, float *t0, float *t1);
float		ft_fmin(float a, float b);
float		ft_fmax(float a, float b);
t_fvector	plane_intersect_point(t_fvector ray, t_fvector ray_origin,t_fvector planenormal, t_fvector planepoint);
t_bool		ray_plane_intersect(t_ray *r, t_object *p, float *t);
t_bool		ray_sphere_intersect(t_ray *r, t_object *s, float *t);
t_bool		ray_cyl_intersect(t_ray *r, t_object *obj, float *result);
t_bool		ray_cone_intersect(t_ray *r, t_object *obj, float *result);

t_fvector	ray_trough_screen(t_fvector start, int sx, int sy);
t_bool		ray_object_intersect(t_ray *ray, t_object *obj, float *t);
t_bool		draw_light(t_ray *ray, t_doom *doom, float *t, int sx, int sy);



#endif
