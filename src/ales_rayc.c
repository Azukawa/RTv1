/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ales_rayc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:46:22 by alero             #+#    #+#             */
/*   Updated: 2022/02/20 21:05:25 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	cone_normal(t_fvector new_start, t_object *object, t_fvector *n)
{
	*n = v_sub(new_start, object->pos);
	*n = v_div(v_mult(*n, v_dot(object->dir, *n)), v_dot(*n, *n));
	*n = v_sub(object->dir, *n);
}

t_fvector	find_object_normal(t_object *object, t_fvector new_start)
{
	t_fvector	n;
	t_fvector	pt;
	t_fvector	temp;
	float		t;

	n = (t_fvector){0, 0, 0};
	if (object->type == SPHERE)
		n = v_sub(new_start, object->pos);
	else if (object->type == PLANE)
	{
		n = object->dir;
		n = v_mult(n, -1);
	}
	else if (object->type == CONE)
		cone_normal(new_start, object, &n);
	else
	{
		temp = v_sub(new_start, object->pos);
		t = v_dot(temp, v_normalize(object->dir));
		pt = v_add(object->pos, v_mult(object->dir, t));
		n = v_sub(new_start, pt);
	}
	return (v_normalize(n));
}

void	iter_screen(t_doom *doom)
{
	doom->sx = 0;
	doom->sy = 0;
	while (doom->sy < WIN_H)
	{
		while (doom->sx < WIN_W)
		{
			raytracer(doom, 0);
			doom->sx++;
		}
		doom->sy++;
		doom->sx = 0;
	}
}

void	ales_rayc(t_doom *doom)
{
	iter_screen(doom);
	doom->run = FALSE;
}
