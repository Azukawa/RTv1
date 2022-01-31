#include "doom.h"

uint32_t	get_color(float r, float g, float b)
{
	int	ir;
	int	ig;
	int	ib;

	ir = (int)(255 * ft_clamp_d(r, 0.0, 1.0));
	ig = (int)(255 * ft_clamp_d(g, 0.0, 1.0));
	ib = (int)(255.00 * ft_clamp_d(b, 0.0, 1.0));
	return (255 << 24 | ir << 16 | ig << 8 | ib);
}

static t_ray	init_ray(t_cam cam, float u, float v)
{
	t_ray	r;

	r.orig = cam.orig;
	r.dir = cam.llc;
	r.dir = mv_add_v(r.dir, mv_mul_f(cam.h, u));
	r.dir = mv_add_v(r.dir, mv_mul_f(cam.v, v));
	r.dir = mv_sub_v(r.dir, cam.orig);
	return (r);
}

//wip
static float	hit_cylinder(t_obj cylinder, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = mv_sub_v(ray.orig, cylinder.pos);
	a = mv_dot_product(ray.dir, ray.dir);
	b = 2.0f * mv_dot_product(oc, ray.dir);
	c = mv_dot_product(oc, oc) - (cylinder.r * cylinder.r);
	discriminant = (b * b) - (4 * a * c);
	if (fabs(discriminant) <= 1.0f)
		return ((-b - sqrtf(discriminant)) / (2.0f * a));
	return (-1.0f);
}

//wip
static float	hit_cone(t_obj cone, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = mv_sub_v(ray.orig, cone.pos);
	a = mv_dot_product(ray.dir, ray.dir);
	b = 2.0f * mv_dot_product(oc, ray.dir);
	c = mv_dot_product(oc, oc) - (cone.r * cone.r);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0f);
	return ((-b - sqrtf(discriminant)) / (2.0f * a));
}

/*
*	Ray hits a plane if the vector from point hit to plane's origin
*	is perpendicular (dotproduct of 0) to the plane's normal (direction) vector.
*	[t] is the distance from the ray's origin to the point hit.
*	Check for very small denominator values avoids cases where there could
*	be infinite or zero hits.
*/
static float	hit_plane(t_obj plane, t_ray ray)
{
	float		denom;
	float		t;
	t_vector	oc;

	denom = mv_dot_product(mv_normalize(ray.orig), mv_normalize(plane.dir));
	if (denom > 0.00001f)
	{
		ft_printf("%f\n", denom);
		oc = mv_sub_v(mv_normalize(plane.pos), mv_normalize(ray.orig));
		t = mv_dot_product(oc, mv_normalize(plane.dir)) / denom;
		if (t < 0)
			return (-1.0f);
		return (t);
	}
	return (-1.0f);
}

static float	hit_sphere(t_obj sphere, t_ray ray)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = mv_sub_v(ray.orig, sphere.pos);
	a = mv_dot_product(ray.dir, ray.dir);
	b = 2.0f * mv_dot_product(oc, ray.dir);
	c = mv_dot_product(oc, oc) - (sphere.r * sphere.r);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1.0f);
	return ((-b - sqrtf(discriminant)) / (2.0f * a));
}

static void	trace_ray(t_doom *doom, t_ray ray, float u, float v)
{
	t_vector	unit_dir;
	float		t;
	uint32_t	col;
	t_vector	n;
	uint		i;

	i = 0;
	while (i < doom->objcount)
	{
		if (doom->object[i].shape == SPHERE)
			t = hit_sphere(doom->object[i], ray);
		if (doom->object[i].shape == PLANE)
		{
			t = hit_plane(doom->object[i], ray);
			ft_printf("%f\n", t);
		}
		if (t > 0.0)
		{
			n = mv_normalize(mv_sub_v(mv_add_v(ray.orig, \
						mv_mul_f(ray.dir, t)), (t_vector){0,0, -1, 1}));
			col = get_color((n.x + 1) / 2, (n.y + 1) / 2, (n.z + 1) / 2);
			return (draw_pixel((uint32_t)(u * WIN_W), (uint32_t)(v * WIN_H), \
			doom->rend.rt_buffer, col));
		}
		i++;
	}
	//else do background stuff
	unit_dir = mv_normalize(ray.dir);
	t = 0.5 * ((double)unit_dir.y + 1.0);
	col = color_lerp(C_PINK, C_PLUM, t);
	draw_pixel((uint32_t)(u * WIN_W), (uint32_t)(v * WIN_H), \
		doom->rend.rt_buffer, col);
}

void	rt_init_cam(t_cam *cam, float vfov, float ar)
{
	float	theta;
	float	h;

	theta = vfov * DEG_TO_RAD;
	h = tanf(theta / 2);
	cam->view_h = 2 * h;
	cam->view_w = ar * cam->view_h;

	cam->view_h = 2.0f;
	cam->view_w = (16 / 9.0f) * cam->view_h;
	cam->focal_l = 1.0f;
	cam->orig = (t_vector){0, 0, 0, 1};
	cam->h = (t_vector){cam->view_w, 0, 0, 1};
	cam->v = (t_vector){0, cam->view_h, 0, 1};
	cam->llc = mv_sub_v(mv_sub_v(mv_sub_v(cam->orig, \
				mv_div_f(cam->h, 2.0f)), mv_div_f(cam->v, 2.0f)), \
		(t_vector){0, 0, cam->focal_l, 1});
	cam->llc = (t_vector){-(cam->view_w / 2), -(cam->view_h / 2), -cam->focal_l, 1.0f};
}

/*
*	Map screen coordinates into UV coordinates (0.0,1.0)
*	going top-to-bottom, left-to-right.
*/
void	rt_render(t_doom *doom)
{
	int		i;
	int		j;
	float	u;
	float	v;

	j = WIN_H;
	while (j >= 0)
	{
		i = 0;
		while (i < WIN_W)
		{
			u = (float)i / (WIN_W - 1);
			v = (float)j / (WIN_H - 1);
			trace_ray(doom, init_ray(doom->cam, u, v), u, v);
			i++;
		}
		j--;
	}
}