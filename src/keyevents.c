/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:37 by esukava           #+#    #+#             */
/*   Updated: 2022/02/20 21:12:41 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	keyevent(t_doom *doom, SDL_Event *e)
{
	if (SDL_WaitEvent(e) > 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_w)
				doom->cam.pos.z -= 5;
			if (e->key.keysym.sym == SDLK_a)
				doom->cam.pos.x -= 5;
			if (e->key.keysym.sym == SDLK_s)
				doom->cam.pos.z += 5;
			if (e->key.keysym.sym == SDLK_d)
				doom->cam.pos.x += 5;
			if (e->key.keysym.sym == SDLK_q)
				doom->cam.rot.y += 5;
			if (e->key.keysym.sym == SDLK_e)
				doom->cam.rot.y -= 5;
			if (e->key.keysym.sym == SDLK_ESCAPE)
				doom->rend.run = FALSE;
			doom->cam.dir = v_rot_xyz(doom->cam.dir, doom->cam.rot);
		}
		else if (e->window.event == SDL_WINDOWEVENT_CLOSE)
			doom->rend.run = FALSE;
		else if (e->type == SDL_WINDOWEVENT \
		&& e->window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_to_window(doom);
		doom->run = TRUE;
	}
}
