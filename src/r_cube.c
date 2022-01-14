/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_cube.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:24:04 by eniini            #+#    #+#             */
/*   Updated: 2022/01/14 16:11:11 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_quad(t_buffer *buf, t_quad proj, int n)
{
	uint32_t	col;

	if (n == 0)
		col = C_GRAPE;
	if (n == 1)
		col = C_BLUE;
	if (n == 2)
		col = C_ICE;
	if (n == 3)
		col = C_LIME;
	if (n == 4)
		col = C_LEMON;
	if (n == 5)
		col = C_ORANGE;
	draw_vector_line(buf, (t_line){(t_ivec3){proj.p[0].x, proj.p[0].y, 0}, \
	(t_ivec3){proj.p[1].x, proj.p[1].y, 0}, 0}, col);
	draw_vector_line(buf, (t_line){(t_ivec3){proj.p[1].x, proj.p[1].y, 0}, \
	(t_ivec3){proj.p[2].x, proj.p[2].y, 0}, 0}, col);
	draw_vector_line(buf, (t_line){(t_ivec3){proj.p[2].x, proj.p[2].y, 0}, \
	(t_ivec3){proj.p[3].x, proj.p[3].y, 0}, 0}, col);
	draw_vector_line(buf, (t_line){(t_ivec3){proj.p[3].x, proj.p[3].y, 0}, \
	(t_ivec3){proj.p[0].x, proj.p[0].y, 0}, 0}, col);
}

/*
*	calculates quad normal with the crossproduct of the first and last
*	lines that make up the quad. Also the normal is normalized.
*
*	Note: dotproduct calculation against camera's position needs to be expanded
*	if in the future camera becomes mobile (not located in 0,0,0)!
*/
static float	get_quad_normal(t_quad *quad_transformed, t_vector cam_pos)
{
	t_vector	normal;
	t_vector	line1;
	t_vector	line2;
	float		normal_len;
	t_vector	camera_ray;

	line1 = mv_substract(quad_transformed->p[1], quad_transformed->p[0]);
	line2 = mv_substract(quad_transformed->p[2], quad_transformed->p[0]);
	normal = mv_normalize(mv_cross_product(line1, line2));
	normal_len = sqrtf(normal.x * normal.x + normal.y * normal.y + \
		normal.z * normal.z);
	normal.x /= normal_len;
	normal.y /= normal_len;
	normal.z /= normal_len;
	camera_ray = mv_substract(quad_transformed->p[0], cam_pos);
	return (mv_dot_product(normal, camera_ray));
}

void	draw_cube (t_doom *doom)
{
	t_quad		quad_projected;
	t_quad		quad_transformed;
	t_mat4		mrot_z;
	t_mat4		mrot_x;
	t_mat4		mat_translation;
	t_mat4		mat_world;
	int			i;
	t_vector	viewoffset;

	mrot_x = mm_init_rotationmatrix_x(doom->world.cube_rotation.x * 0.5);
	mrot_z = mm_init_rotationmatrix_z(doom->world.cube_rotation.z * 0.25);
	mat_translation = mm_init_translation(0.0f, 0.0f, doom->world.cam_distance);
	mat_world = mm_init_unitmatrix();
	mat_world = mm_multiply_matrix(mrot_z, mrot_x);
	mat_world = mm_multiply_matrix(mat_world, mat_translation);
	viewoffset = (t_vector){1.0f, 1.0f, 0, 1};
	i = 0;
	while (i < 6)
	{
		quad_transformed.p[0] = mm_multiply_vector(doom->world.cube[i].p[0], mat_world);
		quad_transformed.p[1] = mm_multiply_vector(doom->world.cube[i].p[1], mat_world);
		quad_transformed.p[2] = mm_multiply_vector(doom->world.cube[i].p[2], mat_world);
		quad_transformed.p[3] = mm_multiply_vector(doom->world.cube[i].p[3], mat_world);
		if (get_quad_normal(&quad_transformed, doom->world.camera) < 0.0f)
		{
			//project to 2D view
			quad_projected.p[0] = mm_multiply_vector(quad_transformed.p[0], doom->world.m_proj);
			quad_projected.p[1] = mm_multiply_vector(quad_transformed.p[1], doom->world.m_proj);
			quad_projected.p[2] = mm_multiply_vector(quad_transformed.p[2], doom->world.m_proj);
			quad_projected.p[3] = mm_multiply_vector(quad_transformed.p[3], doom->world.m_proj);
			//to scale projected coordinates into view, we need to normalize it
			quad_projected.p[0] = mv_divide(quad_projected.p[0], quad_projected.p[0].w);
			quad_projected.p[1] = mv_divide(quad_projected.p[1], quad_projected.p[1].w);
			quad_projected.p[2] = mv_divide(quad_projected.p[2], quad_projected.p[2].w);
			quad_projected.p[3] = mv_divide(quad_projected.p[3], quad_projected.p[3].w);
			//offset into visible screen space
			quad_projected.p[0] = mv_add(quad_projected.p[0], viewoffset);
			quad_projected.p[1] = mv_add(quad_projected.p[1], viewoffset);
			quad_projected.p[2] = mv_add(quad_projected.p[2], viewoffset);
			quad_projected.p[3] = mv_add(quad_projected.p[3], viewoffset);
			quad_projected.p[0].x *= 0.5f * (float)WIN_W;
			quad_projected.p[0].y *= 0.5f * (float)WIN_H;
			quad_projected.p[1].x *= 0.5f * (float)WIN_W;
			quad_projected.p[1].y *= 0.5f * (float)WIN_H;
			quad_projected.p[2].x *= 0.5f * (float)WIN_W;
			quad_projected.p[2].y *= 0.5f * (float)WIN_H;
			quad_projected.p[3].x *= 0.5f * (float)WIN_W;
			quad_projected.p[3].y *= 0.5f * (float)WIN_H;
			draw_quad(doom->rend.win_buffer, quad_projected, i);
		}
		i++;
	}
}
