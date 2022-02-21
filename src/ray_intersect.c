/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:14:57 by esukava           #+#    #+#             */
/*   Updated: 2022/02/21 21:10:54 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_bool	plane_intersect_point(t_fvector ray, t_fvector ray_origin,
t_fvector planenormal, t_fvector planepoint, t_fvector *ret)
{
	t_fvector	diff;
//	t_fvector	ret0;
	t_fvector	ret1;
	t_fvector	ret2;
	float		tempf;
	float		denominator, numerator;

	diff = v_sub(ray_origin, planepoint);
	ret1 = v_add(diff, planepoint);
//	denominator = v_dot(diff, planenormal)
//	numerator = v_dot(ray, planenormal)
//	tempf = -v_dot(diff, planenormal) / v_dot(ray, planenormal);
	denominator = v_dot(diff, planenormal);
	numerator = v_dot(ray, planenormal);
	if ((denominator < 0 && numerator > 0)
		|| (denominator > 0 && numerator < 0))
	{
//		printf("Denominator numerator test TRUE\n");
		//tempf = -denominator / numerator;
		ret->z = -denominator / numerator;
	//	ret2 = v_mult(ray, tempf);
	//	*ret = v_add(ret1, ret2);
		return (TRUE);
	}
//	printf("Denominator numerator test false\n");
	return (FALSE);
}

t_bool  old_ray_plane_intersect(t_ray *r, t_object *p, float *t)
{
    t_fvector   ret;

    if (v_dot(r->dir, p->dir) == 0)
        return (FALSE);

	if(!plane_intersect_point(r->dir, r->start, p->dir, p->pos, &ret))
		return(FALSE);
    if (ret.z <= 0)
        return (FALSE);
    if (ret.z >= *t)
        return (FALSE);
    *t = v_len(v_sub(ret, r->start));
    if (*t <= 0)
        return (FALSE);
    return (TRUE);
}

t_bool	ray_plane_intersect(t_ray *r, t_object *p, float *t)
{
	t_fvector	ret;
	float		dot;

	dot = v_dot(r->dir, p->dir);
	if (fabs(dot) <= 0)
		return (FALSE);
	ret.z = v_dot(v_sub(p->pos, r->start), p->dir) / dot;
	if (ret.z <= 0)
		return (FALSE);
	if (ret.z >= *t)
		return (FALSE);
	//*t = ret.z;
	*t = v_len(v_sub(ret, r->start));
	return (TRUE);
}

// t_bool    intersect_plane(t_v3 ray_dir, t_v3 ray_start,
//     t_object *obj, t_t2 *res)
// {
//     t_v3    ray_obj;
//     float    numerator;
//     float    denominator;

//     vec_normalize(&obj->dir);
//     ray_obj = vec_sub(ray_start, obj->pos);
//     numerator = vec_dot(ray_obj, obj->dir);
//     denominator = vec_dot(ray_dir, obj->dir);
//     if ((denominator < 0 && numerator > 0)
//         || (denominator > 0 && numerator < 0))
//     {
//         res->t0 = -numerator / denominator;
//         res->t1 = -1;
//         return (rt_true);
//     }
//     return (rt_false);
// }

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
	t_fvector	r2o;
	float		t0;
	float		t1;
	float		c_fctr;

//	obj->dir = v_normalize(obj->dir);
	c_fctr = (1 + (obj->angle * DEG_TO_RAD) * (obj->angle * DEG_TO_RAD));
	r2o = v_sub(r->start, obj->pos);
	abc.x = v_dot(r->dir, r->dir) - c_fctr
		* v_dot(r->dir, obj->dir) * v_dot(r->dir, obj->dir);
	abc.y = 2 * (v_dot(r2o, r->dir) - c_fctr * v_dot(r->dir, obj->dir)
			* v_dot(r2o, obj->dir));
	abc.z = v_dot(r2o, r2o) - c_fctr * v_dot(r2o, obj->dir)
		* v_dot(r2o, obj->dir) - obj->r * obj->r;
	quadratic_equation(abc, &t0, &t1);
	t0 = ft_fmin(t0, t1);
//	if (t0 < 0 && t1 > 0)
//		t0 = t1;
	if ((t0 > 0) && (t0 < *result))
	{
		abc = v_add(r->start, v_mult(r->dir, t0));
		if ((v_dot(v_sub(abc, obj->pos), obj->dir) > 0))
			return (FALSE);
		*result = t0;
		return (TRUE);
	}
	return (FALSE);
}
