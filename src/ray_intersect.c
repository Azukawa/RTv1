/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:14:57 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 14:58:59 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_bool	ray_plane_intersect(t_ray *r, t_object *p, float *t)
{
	float	ret;
	float	dot;

	dot = v_dot(r->dir, p->dir);
	if (fabs(dot) <= 0)
		return (FALSE);
	ret = v_dot(v_sub(p->pos, r->start), p->dir) / dot;
	if (ret <= 0)
		return (FALSE);
	if (ret >= *t)
		return (FALSE);
	*t = ret;
	return (TRUE);
}

t_bool	ray_sphere_intersect(t_ray *r, t_object *s, float *t)
{
	float		b;
	float		discr;
	float		t0;
	float		t1;
	t_fvector	dist;

	dist = v_sub(r->start, s->pos);
	b = 2 * v_dot(r->dir, dist);
	discr = b * b - 4 * v_dot(r->dir, r->dir)
		* (v_dot(dist, dist) - (s->r * s->r));
	if (discr < 0)
		return (FALSE);
	discr = sqrtf(discr);
	t0 = (-b + discr) / 2;
	t1 = (-b - discr) / 2;
	if (t0 > t1)
		t0 = t1;
	if ((t0 > 0) && (t0 < *t))
	{
		*t = t0;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ray_cyl_intersect(t_ray *r, t_object *obj, float *result)
{
	t_fvector	r2o;
	t_fvector	abc;
	float		t0;
	float		t1;

	r2o = v_sub(r->start, obj->pos);
	abc.x = v_dot(r->dir, r->dir) - v_dot(r->dir, obj->dir)
		* v_dot(r->dir, obj->dir);
	abc.y = 2 * (v_dot(r2o, r->dir) - v_dot(r->dir, obj->dir)
			* v_dot(r2o, obj->dir));
	abc.z = v_dot(r2o, r2o) - v_dot(r2o, obj->dir)
		* v_dot(r2o, obj->dir) - obj->r * obj->r;
	quadratic_equation(abc, &t0, &t1);
	t0 = ft_fmin(t0, t1);
	if ((t0 > 0) && (t0 < *result))
	{
		*result = t0;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ray_cone_intersect(t_ray *r, t_object *obj, float *result)
{
	t_fvector	abc;
	float		t0;
	float		t1;
	float		c_fctr;

    c_fctr = pow(cos(0.7), 2);
    t_fvector oc = v_sub(r->start, obj->pos);
    t_fvector V = v_normalize(v_sub(obj->dir, obj->pos));
    float D_V = v_dot(r->dir, V);
    float CO_V = v_dot(oc, V);
    abc.x = pow(D_V, 2) - c_fctr;
    abc.y = 2.0 * (D_V * CO_V - v_dot(r->dir, oc) * c_fctr);
    abc.z = pow(CO_V, 2) - v_dot(oc, oc) * c_fctr;
	quadratic_equation(abc, &t0, &t1);
	t0 = ft_fmin(t0, t1);
	if ((t0 > 0.01) && (t0 < *result))
	{
		abc = v_add(r->start, v_mult(r->dir, t0));
		if ((v_dot(v_sub(abc, obj->pos), obj->dir) > 0))
			return (FALSE);
		*result = t0;
		return (TRUE);
	}
	return (FALSE);
}
