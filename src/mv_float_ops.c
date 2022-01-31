/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_float_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:23:02 by eniini            #+#    #+#             */
/*   Updated: 2022/01/25 16:16:21 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_utils.h"

//	Add a scalar value [f] to the vector [v].
t_vector	mv_add_f(t_vector v, float f)
{
	t_vector	vector;

	vector.x = v.x + f;
	vector.y = v.y + f;
	vector.z = v.z + f;
	vector.w = v.w + f;
	return (vector);
}

//	Substract a scalar value [f] from the vector [v].
t_vector	mv_sub_f(t_vector v, float f)
{
	t_vector	vector;

	vector.x = v.x - f;
	vector.y = v.y - f;
	vector.z = v.z - f;
	vector.w = v.w - f;
	return (vector);
}

//	Multiply the vector [v] with a scalar value [f].
t_vector	mv_mul_f(t_vector v, float f)
{
	t_vector	vector;

	vector.x = v.x * f;
	vector.y = v.y * f;
	vector.z = v.z * f;
	vector.w = v.w * f;
	return (vector);
}

//Divide the vector [f] with a scalar value [f].
t_vector	mv_div_f(t_vector v, float f)
{
	t_vector	vector;

	vector.x = v.x / f;
	vector.y = v.y / f;
	vector.z = v.z / f;
	vector.w = v.w / f;
	return (vector);
}
