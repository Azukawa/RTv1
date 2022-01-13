/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:22:33 by eniini            #+#    #+#             */
/*   Updated: 2022/01/13 21:25:54 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_player(t_doom *doom)
{
	doom->keys.up_pressed = FALSE;
	doom->keys.down_pressed = FALSE;
	doom->keys.left_pressed = FALSE;
	doom->keys.right_pressed = FALSE;
	doom->keys.fps_switch = FALSE;
	doom->keys.mouse_switch = FALSE;
	doom->keys.rot_switch = TRUE;
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
static void	init(t_doom *doom)
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
	init_player(doom);
}

static void	cleanup(t_doom *doom)
{
	SDL_DestroyTexture(doom->rend.win_tex);
	SDL_DestroyRenderer(doom->rend.renderer);
	SDL_DestroyWindow(doom->rend.win);
	free(doom->rend.win_buffer->px);
	free(doom->rend.win_buffer);
	cleanup_tests(doom);
	SDL_Quit();
}

/*
*	Note about SDL_LockTexture: void **px is 'filled in', meaning that SDL
*	creates its own allocated pixel buffer thats returned to the given pointer.
*	This is why you need to query for the pixel_pitch too since its the only
*	way to know the 1-directional pitch of the created buffer.
*/
static void	loop(t_doom	*doom)
{
	SDL_Event	e;

	ft_bzero(doom->rend.win_buffer->px, WIN_H * WIN_W * sizeof(uint32_t));
	keyevent(doom, &e);
	mouse_movement(doom);
	dotests(doom);
	fps_counter(&doom->global_fps);
	if (SDL_LockTexture(doom->rend.win_tex, NULL, \
		&doom->rend.win_pixels, &doom->rend.win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(doom->rend.win_pixels, doom->rend.win_buffer->px, \
	WIN_H * doom->rend.win_pixel_pitch);
	SDL_UnlockTexture(doom->rend.win_tex);
	if (SDL_RenderCopy(doom->rend.renderer, doom->rend.win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(doom->rend.renderer);
	if (doom->keys.fps_switch == TRUE)
		SDL_Delay(40);
}

int	main(void)
{
	t_doom		doom;

	ft_bzero(&doom.rend, sizeof(t_rend));
	doom.rend.win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!doom.rend.win_buffer)
		ft_getout("failed to initialize main buffer");
	doom.rend.win_buffer->w = WIN_W;
	doom.rend.win_buffer->h = WIN_H;
	doom.rend.win_buffer->px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	init(&doom);
	init_tests(&doom);
	while (doom.rend.run)
		loop(&doom);
	cleanup(&doom);
	return (0);
}
