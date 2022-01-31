/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:24:59 by eniini            #+#    #+#             */
/*   Updated: 2022/01/31 22:36:55 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	allocate_sphere(t_obj *obj, t_vector orig, float radius)
{
	obj->shape = SPHERE;
	obj->pos = orig;
	obj->dir = orig;
	obj->r = radius;
}

static void	allocate_plane(t_obj *obj, t_vector orig, t_vector direction)
{
	obj->shape = PLANE;
	obj->pos = orig;
	obj->dir = mv_normalize(direction);
	obj->r = 0.0f;
}

static void	init_objects(t_doom *doom)
{
	float r = cos(M_1_PI / 4);

	doom->object = (t_obj *)malloc(sizeof(t_obj) * 2);
	if (!doom->object)
		ft_getout("failed to allocate objects");
	//allocate_sphere(&doom->object[0], (t_vector){-r,0,-1, 1}, r);
	allocate_sphere(&doom->object[0], (t_vector){0, 0, -1, 1}, 0.5);
	allocate_plane(&doom->object[1], (t_vector){0, -1, -1, 1}, (t_vector){0, 0, -0.5, 1});
	//allocate_sphere(&doom->object[1], (t_vector){r,0,-1, 1}, r);
	//doom->objcount = 2;
	doom->objcount = 2;
}

void	init_tests(t_doom *doom)
{
	doom->world.tricount = 12;
	doom->world.cube_rotation = (t_vector){1, 1, 1, 1};
	doom->world.camera = (t_vector){0, 0, 0, 1};
	doom->world.cam_fov = 90;
	doom->world.cam_distance = 4;
	init_objects(doom);
	rt_init_cam(&doom->cam, 90, 16 / 9);
	rt_render(doom);
	ft_printf("render complete!\n");
}

void	cleanup_tests(t_doom *doom)
{
	if (doom->object)
		free(doom->object);
}

void	dotests(t_doom *doom)
{
	ft_memcpy(doom->rend.win_buffer->px, doom->rend.rt_buffer->px,
	WIN_H * WIN_W * sizeof(uint32_t));
}
