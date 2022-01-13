/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_testing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:24:09 by eniini            #+#    #+#             */
/*   Updated: 2022/01/13 21:24:41 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	r_dotests(t_doom *doom)
{
	draw_cube(doom);
	if (doom->keys.rot_switch == TRUE)
	{
		doom->world.cube_rotation.x += 0.001;
		doom->world.cube_rotation.z += 0.001;
	}
}
