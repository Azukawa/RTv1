/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:41:48 by alero             #+#    #+#             */
/*   Updated: 2022/02/16 12:50:52 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fvector	ray_trough_screen(t_fvector start, int sx, int sy)
{
	t_fvector ray_dir;
	t_fvector pixel;	

	pixel.x = lerp1d(-1.0, 1.0, (1.0f / WIN_W) * (sx + 0.5));
	pixel.y = lerp1d(-0.75, 0.75, (1.0f/WIN_H) * (sy + 0.5));
	pixel.z = 1;
	ray_dir = v_normalize(v_sub(pixel, start));
	return (ray_dir);

}

t_bool	ray_object_intersect(t_ray *ray, t_object *obj, float *t)
{
	if(obj->type == SPHERE)	
		return(ray_sphere_intersect(ray , obj, t));
	else if(obj->type == PLANE) 
		return(ray_plane_intersect(ray, obj, t));
	else if(obj->type == CYL) 
		return(ray_cyl_intersect(ray, obj, t));
	else if(obj->type == CONE)
		return(ray_cone_intersect(ray, obj, t));
	return (FALSE);
}

t_bool	draw_light(t_ray *ray, t_doom *doom, float *t, int sx, int sy)
{
	if(ray_sphere_intersect(ray, &doom->object[9], t))
	{	
		draw_pixel(sx, sy, doom->rend.win_buffer, 0xFFFF00);
		return(TRUE);
	}
	return(FALSE);
}


