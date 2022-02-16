/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:44:33 by alero             #+#    #+#             */
/*   Updated: 2022/02/16 19:26:01 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	keyevent(t_doom *doom, SDL_Event *e)
{
	if(SDL_WaitEvent(e) > 0)
	{
		if(e->type == SDL_KEYDOWN)
		{	
			if (e->key.keysym.sym == SDLK_ESCAPE)
				doom->rend.run = FALSE;
			else if (e->key.keysym.sym == 1073741916)
				doom->xvar -= 1;
			else if (e->key.keysym.sym == 1073741918)
				doom->xvar += 1;
			else if (e->key.keysym.sym == 1073741920)
				doom->yvar -= 1;
			else if (e->key.keysym.sym == 1073741914)
				doom->yvar += 1;
			else if (e->key.keysym.sym == 1073741919)
				doom->zvar += 1;
			else if (e->key.keysym.sym == 1073741913)
				doom->zvar -= 1;	
		}
		else if (e->window.event == SDL_WINDOWEVENT_CLOSE)
			doom->rend.run = FALSE;	
		else if(e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_to_window(doom);	
		doom->run = TRUE;
	}
}
