/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_operations copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:23:02 by eniini            #+#    #+#             */
/*   Updated: 2022/01/25 15:39:12 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_utils.h"

t_vector	mv_add_v(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x + vb.x;
	vector.y = va.y + vb.y;
	vector.z = va.z + vb.z;
	vector.w = va.w + vb.z;
	return (vector);
}

t_vector	mv_sub_v(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x - vb.x;
	vector.y = va.y - vb.y;
	vector.z = va.z - vb.z;
	vector.w = va.w - vb.w;
	return (vector);
}

t_vector	mv_mul_v(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x * vb.x;
	vector.y = va.y * vb.y;
	vector.z = va.z * vb.z;
	vector.w = va.w * vb.w;
	return (vector);
}

t_vector	mv_div_v(t_vector va, t_vector vb)
{
	t_vector	vector;

	vector.x = va.x / vb.x;
	vector.y = va.y / vb.y;
	vector.z = va.z / vb.z;
	vector.w = va.w / vb.w;
	return (vector);
}
