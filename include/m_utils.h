/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:24 by eniini            #+#    #+#             */
/*   Updated: 2022/01/25 16:16:47 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_UTILS_H
# define M_UTILS_H

# include "defines.h"

//vector operations

t_vector	mv_add_f(t_vector v, float f);
t_vector	mv_sub_f(t_vector v, float f);
t_vector	mv_mul_f(t_vector v, float f);
t_vector	mv_div_f(t_vector v, float f);

t_vector	mv_add_v(t_vector va, t_vector vb);
t_vector	mv_sub_v(t_vector va, t_vector vb);
t_vector	mv_mul_v(t_vector va, t_vector vb);
t_vector	mv_div_v(t_vector va, t_vector vb);

float		mv_length(t_vector v);
float		mv_distance_to_vector(t_vector va, t_vector vb);

t_vector	mv_normalize(t_vector v);

float		mv_dot_product(t_vector va, t_vector vb);

t_vector	mv_cross_product(t_vector va, t_vector vb);

//4x4 matrix funcs

t_vector	mm_multiply_vector(t_vector v, t_mat4 m);

t_mat4		mm_multiply_matrix(t_mat4 ma, t_mat4 mb);

t_mat4		mm_init_unitmatrix(void);

t_mat4		mm_init_rotationmatrix_x(float angle_in_rads);
t_mat4		mm_init_rotationmatrix_y(float angle_in_rads);
t_mat4		mm_init_rotationmatrix_z(float angle_in_rads);

t_mat4		mm_init_translation(float x, float y, float z);

t_mat4		mm_init_3d_projection(float fov, float ar, float near, float far);

#endif
