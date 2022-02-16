#include "doom.h"

t_fvector	find_object_normal(t_object *object, t_fvector new_start)
{
	t_fvector	n;
	t_fvector	temp;
	float		t;
	n = (t_fvector){0, 0, 0};
	
	if(object->type == SPHERE)
		n = v_sub(new_start, object->pos);
	else if(object->type == PLANE)
	{
		n = object->dir;
		n = v_mult(n, -1);
	}
	else if(object->type == CONE)
	{
		n = v_sub(new_start, object->pos);
		n = v_div(v_mult(n, v_dot(object->dir, n)), v_dot(n, n));
		n = v_sub(object->dir, n);
	}
	else// if(object->type == CYL)
	{
		temp = v_sub(new_start, object->pos);
		t = v_dot(temp, v_normalize(object->dir));
   		t_fvector	pt = v_add(object->pos, v_mult(object->dir, t));
   		n = v_sub(new_start, pt);
	}
	return(v_normalize(n));	
}

void	calculate_lighting(t_doom *doom, t_fvector n, t_fvector new_start, float t, int cur_obj, uint32_t *color)
{
	float red, green, blue;
	t_ray light_ray;
	t_bool in_shadow;
	t_material current_mat = doom->material[doom->object[cur_obj].material];
	red = green = blue = 0;	
	t_fvector dist = v_sub(doom->object[9].pos, new_start);
	float t1;
	if(v_dot(n, dist) <= 0)
		return ;
	t1 = sqrtf(v_dot(dist, dist));
	if(t1 <= 0)
		return ;
	light_ray.start = new_start;
	light_ray.dir = v_mult(dist, (1/t1));
	in_shadow = FALSE;
	int	k = 0;
	while(k < doom->object_count)
	{
		if(v_dot(n, dist) > 0 && k != cur_obj && ray_object_intersect(&light_ray, &doom->object[k], &t1))
		{				
			in_shadow = TRUE;
			return ;
		}
		k++;
	}
	if(!in_shadow /*&& mfv_dot_product(n, light_ray.dir) >0*/ )
	{
		float lambert = v_dot(light_ray.dir, n);
		red = red + lambert * doom->object[9].intensity.red * current_mat.diffuse.red;
		green = green + lambert * doom->object[9].intensity.green * current_mat.diffuse.green;
		blue = blue + lambert * doom->object[9].intensity.blue * current_mat.diffuse.blue;
	}
	*color = get_color2(ft_fmin(red * 255.0f, 255.0f), ft_fmin(green * 255.0f, 255.0f), ft_fmin(blue * 255.0f, 255.0f));
	return ;
}

void	raytracer(t_doom *doom, int sx, int sy)
{
	t_ray		ray;
	uint32_t	color;
	float		t;
	int			cur_obj;
	int			i;
	t_fvector	n;

	color = 0x00000000;
	ray.start.x = 0;
	ray.start.y = 0;
	ray.start.z = 0;
	ray.dir = ray_trough_screen(ray.start, sx, sy);
	
	t = 20000.0f;
	cur_obj= -1;
	i = 0;
	while(i < doom->object_count)
	{
		if(ray_object_intersect(&ray, &doom->object[i], &t))
			cur_obj = i;
		i++;
	}
	if(draw_light(&ray, doom, &t, sx, sy))
		return ;
	if(cur_obj == -1)
	{
		draw_pixel(sx, sy, doom->rend.win_buffer, color);
		return ;
	}
	t_fvector	new_start = v_add(ray.start, v_mult(ray.dir, t));
	n = find_object_normal(&doom->object[cur_obj], new_start);
	calculate_lighting(doom, n, new_start, t, cur_obj, &color);		
	draw_pixel(sx, sy, doom->rend.win_buffer, color);
}

void	iter_screen(t_doom *doom)
{
	uint32_t sx, sy;
	sy = sx = 0;
	while (sy < WIN_H)
	{	
		while(sx < WIN_W)
		{
			raytracer(doom, sx, sy);
			sx++;
		}
	sy++;
	sx = 0;
	}
}

void ales_rayc(t_doom *doom)
{		
	doom->object[9].pos.x += doom->xvar;
	doom->object[9].pos.y += doom->yvar;
	doom->object[9].pos.z += doom->zvar;
	
	doom->xvar = 0;
	doom->yvar = 0;
	doom->zvar = 0;
	iter_screen(doom);
}
