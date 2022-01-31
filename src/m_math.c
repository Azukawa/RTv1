/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:22:27 by eniini            #+#    #+#             */
/*   Updated: 2022/01/31 22:01:30 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
*	Applies a 2d matrix rotation to [rot_point] around the [pivot_point].
*	Since rotation matrix rotates around the origin point, we need to translate
*	to-be-rotated point back to origin, and apply translation back afterwards.
*	Because our Y-axis points down, this rotates clockwise. Reverse rotation
*	can be done with negative [angle] values.
*/
t_vector	vector_2drotate(t_vector rotation_p, t_vector pivot_p, float angle)
{
	t_vector	o_rot_result;
	float		c;
	float		s;

	angle = (int)angle % 360;
	c = cosf(angle * DEG_TO_RAD);
	s = sinf(angle * DEG_TO_RAD);
	rotation_p.x -= pivot_p.x;
	rotation_p.y -= pivot_p.y;
	o_rot_result.x = roundf(rotation_p.x * c - rotation_p.y * s);
	o_rot_result.y = roundf(rotation_p.x * s + rotation_p.y * c);
	rotation_p.x = o_rot_result.x + pivot_p.x;
	rotation_p.y = o_rot_result.y + pivot_p.y;
	rotation_p.z = 0.0f;
	rotation_p.w = 1.0f;
	return (rotation_p);
}
