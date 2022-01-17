/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:24:59 by eniini            #+#    #+#             */
/*   Updated: 2022/01/14 21:06:42 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_tests(t_doom *doom)
{
	doom->world.tricount = 12;
	doom->world.cube_rotation = (t_vector){1, 1, 1, 1};
	doom->world.camera = (t_vector){0, 0, 0, 1};
	doom->world.cam_fov = 90;
	doom->world.cam_distance = 4;

	doom->world.cube = init_cube();
	if (doom->world.cube)
		set_cube(doom->world.cube, (t_fvec3){1,1,1}, (t_fvec3){0, 0, 0});

	doom->world.sphere = init_sphere();
	if (doom->world.sphere)
		set_sphere(doom->world.sphere, 10.f);

	doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
	(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
}

void	cleanup_tests(t_doom *doom)
{
	if (doom->world.cube)
		free(doom->world.cube);
}

void	dotests(t_doom *doom)
{
	r_dotests(doom);
}
