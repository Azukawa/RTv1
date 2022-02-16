/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:22:33 by eniini            #+#    #+#             */
/*   Updated: 2022/02/16 19:09:52 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_player(t_doom *doom)
{
	doom->sx = 0;
	doom->sy = 0;
	doom->xvar = 0;
	doom->yvar = 0;
	doom->zvar = 0;
	doom->cam.pos.x = 0;
	doom->cam.pos.y = 0;
	doom->cam.pos.z = 0;
	doom->cam.rot.x = 0;
	doom->cam.rot.y = 0;
	doom->cam.rot.z = 0;
	doom->cam.dir = v_rot_xyz(doom->cam.dir, doom->cam.rot);
	doom->object_count = 3;
	doom->run = TRUE;

	doom->object[0].pos.z = 20;
	doom->object[0].pos.x = 0;
	doom->object[0].pos.y = 0;
	doom->object[0].dir.x = 1;
	doom->object[0].dir.y = 0;
	doom->object[0].dir.z = 0;
	doom->object[0].r = 3;
	doom->object[0].material = 2;
	doom->object[0].type = CYL;
	doom->object[0].angle = 1;

	doom->object[1].pos.z = 20;
	doom->object[1].pos.x = 7;
	doom->object[1].pos.y = 0;
	doom->object[1].dir.x = 0;
	doom->object[1].dir.y = 1;
	doom->object[1].dir.z = 0;
	doom->object[1].r = 0;
	doom->object[1].angle = 1;
	doom->object[1].type = CONE;
	doom->object[1].material = 0;
	
	doom->object[2].pos.z = 40;
	doom->object[2].pos.x = 0;
	doom->object[2].pos.y = 5;
	doom->object[2].r = 5;
	doom->object[2].type = PLANE;
	doom->object[2].material = 1;
	doom->object[2].dir.x = 0;
	doom->object[2].dir.y = 0;
	doom->object[2].dir.z = 1;

	doom->object[3].pos.z = 15;
	doom->object[3].pos.x = 7;
	doom->object[3].pos.y = 0;
	doom->object[3].dir.x = 0;
	doom->object[3].dir.y = 1;
	doom->object[3].dir.z = 0;
	doom->object[3].r = 3;
	doom->object[3].angle = 0;
	doom->object[3].type = CONE;
	doom->object[3].material = 0;
	
	doom->object[9].pos.z = 0;
	doom->object[9].pos.x = 0;
	doom->object[9].pos.y = 0;
	doom->object[9].r = 1;
	doom->object[9].type = LIGHT;
	doom->object[9].intensity.red = 1;
	doom->object[9].intensity.green = 1;
	doom->object[9].intensity.blue = 1;

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


//	doom->sphere[0].pos.z = 300;
//	doom->sphere[0].pos.x = WIN_W/2;
//	doom->sphere[0].pos.y = WIN_H/2;
//	doom->sphere[0].r = 50;
//	doom->sphere[0].material = 0;

//	doom->sphere[1].pos.z = 1200;
//	doom->sphere[1].pos.x = -400;
//	doom->sphere[1].pos.y = -400;
//	doom->sphere[1].r = 400;
//	doom->sphere[1].material = 1;

//	doom->plane[0].pos.x = WIN_W / 2 + 30;
//	doom->plane[0].pos.y = WIN_H / 2 + 300;
//	doom->plane[0].pos.z = 100;
//	doom->plane[0].dir.x = 0;
//	doom->plane[0].dir.y = 1;
//	doom->plane[0].dir.z = 0;
//	doom->plane[0].material = 2;

//	doom->cylinder[0].pos.x = 100;
//	doom->cylinder[0].pos.y = 100;
//	doom->cylinder[0].pos.z = 100;
//	doom->cylinder[0].dir.x = 0.1;
//	doom->cylinder[0].dir.y = 1;
//	doom->cylinder[0].dir.z = 0;
//	doom->cylinder[0].r = 70;
//	doom->plane[0].material = 0;
	
//	doom->cone[0].pos.x = 200;
//	doom->cone[0].pos.y = 200;
//	doom->cone[0].pos.z = 200;
//	doom->cone[0].dir.x = 1;
//	doom->cone[0].dir.y = 0;
//	doom->cone[0].dir.z = 0;
//	doom->cone[0].r = 0;
//	doom->cone[0].angle = 1 ;
	
	doom->light[0].pos.x = 0;//WIN_W/2;
	doom->light[0].pos.y = 0;//WIN_H/2;
	doom->light[0].pos.z = 0;
	doom->light[0].intensity.red = 0.1;
	doom->light[0].intensity.green = 0.1;
	doom->light[0].intensity.blue = 0.1;

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
	free(doom->rend.win_buffer.px);
	SDL_Quit();
}

void		draw_to_window(t_doom *doom)
{
		if (SDL_LockTexture(doom->rend.win_tex, NULL, \
			&doom->rend.win_pixels, &doom->rend.win_pixel_pitch) < 0)
			ft_getout(SDL_GetError());
		ft_memcpy(doom->rend.win_pixels, doom->rend.win_buffer.px, \
		WIN_H * doom->rend.win_pixel_pitch);
		SDL_UnlockTexture(doom->rend.win_tex);
		if (SDL_RenderCopy(doom->rend.renderer, doom->rend.win_tex, NULL, NULL) < 0)
			ft_getout(SDL_GetError());
		SDL_RenderPresent(doom->rend.renderer);
	
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

//	SDL_PollEvent(&e);
	SDL_WaitEvent(&e);
	if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		doom->rend.run = FALSE;

	
	keyevent(doom, &e);
	if(doom->run == TRUE)	
	{
		ft_bzero(doom->rend.win_buffer.px, WIN_H * WIN_W * sizeof(uint32_t));
		ales_rayc(doom);
		draw_to_window(doom);
	}
}

int	main(void)
{
	t_doom		doom;

	ft_bzero(&doom.rend, sizeof(t_rend));
//	doom.rend.win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
//	if (!doom.rend.win_buffer)
//		ft_getout("failed to initialize main buffer");
	doom.rend.win_buffer.w = WIN_W;
	doom.rend.win_buffer.h = WIN_H;
	if(!(doom.rend.win_buffer.px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W)))
	{
		write(1, "fail to malloc\n", 20);
		doom.rend.win_buffer.px = NULL;
		cleanup(&doom);
		return(-1);
	}
	init(&doom);
	while (doom.rend.run)
		loop(&doom);
	cleanup(&doom);
	return (0);
}
