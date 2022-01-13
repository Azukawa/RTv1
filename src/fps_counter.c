/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:22:08 by eniini            #+#    #+#             */
/*   Updated: 2022/01/13 21:22:11 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fps_counter(int *global_fps)
{
	static int		i;
	static size_t	sec;
	static size_t	presec;

	sec = SDL_GetTicks();
	if (sec - presec < 1000)
	{
		i++;
	}
	else
	{
		presec = sec;
		*global_fps = i;
		i = 0;
	}
}
