/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:02:27 by esukava           #+#    #+#             */
/*   Updated: 2022/02/19 20:30:48 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_material(t_doom *doom)
{
	doom->material[0].diffuse.red = 1;
	doom->material[0].diffuse.green = 0;
	doom->material[0].diffuse.blue = 0;
	doom->material[0].reflection = 1;
	doom->material[1].diffuse.red = 0.7;
	doom->material[1].diffuse.green = 0.7;
	doom->material[1].diffuse.blue = 0.7;
	doom->material[1].reflection = 1;
	doom->material[2].diffuse.red = 0;
	doom->material[2].diffuse.green = 0;
	doom->material[2].diffuse.blue = 1;
	doom->material[2].reflection = 1;
}

void	init_light(t_doom *doom)
{
	doom->object[9].r = 1;
	doom->object[9].type = LIGHT;
	doom->object[9].intensity.red = 1;
	doom->object[9].intensity.green = 1;
	doom->object[9].intensity.blue = 1;
	doom->light[0].pos.x = 0;
	doom->light[0].pos.y = 0;
	doom->light[0].pos.z = 0;
	doom->light[0].intensity.red = 0.1;
	doom->light[0].intensity.green = 0.1;
	doom->light[0].intensity.blue = 0.1;
}

void	init_player(t_doom *doom)
{
	doom->sx = 0;
	doom->sy = 0;
	doom->cam.pos.x = 0;
	doom->cam.pos.y = 0;
	doom->cam.pos.z = 0;
	doom->cam.rot.x = 0;
	doom->cam.rot.y = 0;
	doom->cam.rot.z = 0;
	doom->cam.dir = v_rot_xyz(doom->cam.dir, doom->cam.rot);
	doom->object_count = 2;
	doom->run = TRUE;
}

/*
*	Todo:	read up on windowflags in case we could have additional features
*			Q:do we need sethint() and should it be to linear or nearest?
*			same thing with rendermodes, pixelformat etc.
*			A:Currently we don't use any SDL texture transformation funcs so its
*			probably not needed!
*			blending is only needed if we work with multiple texture layers
*			(and if we want to blend them together)
*/
void	init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_getout(SDL_GetError());
	doom->rend.win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!doom->rend.win)
		ft_getout(SDL_GetError());
	doom->rend.renderer = SDL_CreateRenderer(doom->rend.win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!doom->rend.renderer)
		ft_getout(SDL_GetError());
	doom->rend.win_tex = SDL_CreateTexture(doom->rend.renderer, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!doom->rend.win_tex)
		ft_getout(SDL_GetError());
	doom->rend.run = TRUE;
	init_material(doom);
	init_light(doom);
	init_player(doom);
}
