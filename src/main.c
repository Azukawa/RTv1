/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:47 by esukava           #+#    #+#             */
/*   Updated: 2022/02/20 21:12:50 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	cleanup(t_doom *doom)
{
	SDL_DestroyTexture(doom->rend.win_tex);
	SDL_DestroyRenderer(doom->rend.renderer);
	SDL_DestroyWindow(doom->rend.win);
	free(doom->rend.win_buffer.px);
	SDL_Quit();
}

void	draw_to_window(t_doom *doom)
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

	SDL_WaitEvent(&e);
	if (e.window.event == SDL_WINDOWEVENT_CLOSE)
		doom->rend.run = FALSE;
	keyevent(doom, &e);
	if (doom->run == TRUE)
	{
		ft_bzero(doom->rend.win_buffer.px, WIN_H * WIN_W * sizeof(uint32_t));
		ales_rayc(doom);
		draw_to_window(doom);
	}
}

int	main1(int argc, char **argv)
{
	t_doom		doom;

	ft_bzero(&doom, sizeof(t_doom));
	doom.rend.win_buffer.w = WIN_W;
	doom.rend.win_buffer.h = WIN_H;
	doom.rend.win_buffer.px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	if (!doom.rend.win_buffer.px)
	{
		write(1, "fail to malloc\n", 20);
		doom.rend.win_buffer.px = NULL;
		cleanup(&doom);
		return (-1);
	}
	init(&doom);
	if (parse(argv[1], &doom))
		while (doom.rend.run)
			loop(&doom);
	parse(argv[1], &doom);
	cleanup(&doom);
	return (0);
}

int	main(int argc, char **argv)
{
	main1(argc, argv);
	system("leaks -q RTv1");
}
