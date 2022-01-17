/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:23:02 by eniini            #+#    #+#             */
/*   Updated: 2022/01/14 20:48:25 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_utils.h"

t_vector	mv_add(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x + vb.x;
	vector.y = va.y + vb.y;
	vector.z = va.z + vb.z;
	vector.w = va.w + vb.z;
	return (vector);
}

t_vector	mv_substract(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x - vb.x;
	vector.y = va.y - vb.y;
	vector.z = va.z - vb.z;
	vector.w = va.w - vb.w;
	return (vector);
}

t_vector	mv_multiply(t_vector v, float multiplier)
{
	t_vector	vector;

	vector.x = v.x * multiplier;
	vector.y = v.y * multiplier;
	vector.z = v.z * multiplier;
	vector.w = v.w * multiplier;
	return (vector);
}

t_vector	mv_divide(t_vector v, float divisor)
{
	t_vector	vector;

	vector.x = v.x / divisor;
	vector.y = v.y / divisor;
	vector.z = v.z / divisor;
	vector.w = v.w / divisor;
	return (vector);
}
