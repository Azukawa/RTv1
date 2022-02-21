/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:13:52 by esukava           #+#    #+#             */
/*   Updated: 2022/02/21 21:14:21 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_ray	ray_trough_screen(t_doom *doom)
{
	t_ray		ret;
	t_fvector	pixel;

	ret.start = doom->cam.pos;
	pixel.x = lerp1d(-1.0, 1.0, (1.0f / WIN_W) * (doom->sx + 0.5));
	pixel.y = lerp1d(-0.75, 0.75, (1.0f / WIN_H) * (doom->sy + 0.5));
	pixel.z = 1;
	pixel = v_rot_xyz(pixel, doom->cam.rot);
	ret.dir = v_normalize(pixel);
	return (ret);
}

t_bool	ray_object_intersect(t_ray *ray, t_object *obj, float *t)
{
	if (obj->type == SPHERE)
		return (ray_sphere_intersect(ray, obj, t));
	else if (obj->type == PLANE)
	//	return (old_ray_plane_intersect(ray, obj, t));
		return (ray_plane_intersect(ray, obj, t));
	else if (obj->type == CYL)
		return (ray_cyl_intersect(ray, obj, t));
	else if (obj->type == CONE)
		return (ray_cone_intersect(ray, obj, t));
	return (FALSE);
}

t_bool	draw_light(t_ray *ray, t_doom *doom, float *t)
{
	if (ray_sphere_intersect(ray, &doom->object[9], t))
	{
		draw_pixel(doom->sx, doom->sy, &doom->rend.win_buffer, 0xFFFF00);
		return (TRUE);
	}
	return (FALSE);
}
