#include "doom.h"

t_quad	*init_cube(void)
{
	t_quad	*cube;

	cube = (t_quad *)malloc(sizeof(t_quad) * QUADCOUNT_CUBE);
	if (!cube)
		return (NULL);
	return (cube);
}

/*
*	d(x,y,z) = dimensions
*	p(x,y,z) = position
*/
void	set_cube(t_quad *c, t_fvec3 d, t_fvec3 p)
{
	c[0].p[0] = (t_vector){p.x, p.y, p.z, 1.0f};
	c[0].p[1] = (t_vector){p.x, (p.y + d.y), p.z, 1.0f};
	c[0].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1.0f};
	c[0].p[3] = (t_vector){(p.x + d.x), p.y, p.z, 1.0f};
	c[1].p[0] = (t_vector){(p.x + d.x), p.y, p.z, 1.0f};
	c[1].p[1] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1.0f};
	c[1].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1.0f};
	c[1].p[3] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1.0f};
	c[2].p[0] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1.0f};
	c[2].p[1] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1.0f};
	c[2].p[2] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1.0f};
	c[2].p[3] = (t_vector){p.x, p.y, (p.z + d.z), 1.0f};
	c[3].p[0] = (t_vector){p.x, p.y, (p.z + d.z), 1.0f};
	c[3].p[1] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1.0f};
	c[3].p[2] = (t_vector){p.x, (p.y + d.y), p.z, 1.0f};
	c[3].p[3] = (t_vector){p.x, p.y, p.z, 1.0f};
	c[4].p[0] = (t_vector){p.x, (p.y + d.y), p.z, 1.0f};
	c[4].p[1] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1.0f};
	c[4].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1.0f};
	c[4].p[3] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1.0f};
	c[5].p[0] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1.0f};
	c[5].p[1] = (t_vector){p.x, p.y, (p.z + d.z), 1.0f};
	c[5].p[2] = (t_vector){p.x, p.y, p.z, 1.0f};
	c[5].p[3] = (t_vector){(p.x + d.x), p.y, p.z, 1.0f};
}

t_tri *init_sphere(void)
{
	t_tri	*sphere;

	sphere = (t_tri *)malloc(sizeof(t_tri) * TRICOUNT_SPHERE);
	if (!sphere)
		return (NULL);
	return (sphere);
}

static void	setup_vectors(t_vector *v)
{
	float	t;

	t = (1.f + sqrtf(5.f)) / 2.f;
	v[0] = (t_vector){-1, t, 0, 1};
	v[1] = (t_vector){1, t, 0, 1};
	v[2] = (t_vector){-1, -t, 0, 1};
	v[3] = (t_vector){1, -t, 0, 1};
	v[4] = (t_vector){0, -1, t, 1};
	v[5] = (t_vector){0, 1, t, 1};
	v[6] = (t_vector){0, -1, -t, 1};
	v[7] = (t_vector){0, 1, -t, 1};
	v[8] = (t_vector){t, 0, -1, 1};
	v[9] = (t_vector){t, 0, 1, 1};
	v[10] = (t_vector){-t, 0, -1, 1};
	v[11] = (t_vector){-t, 0, 1, 1};
}

static void spherize(t_tri *sphere, float radius)
{
	int	i;

	i = 0;
	while (i < TRICOUNT_SPHERE)
	{
		sphere[i].p[0] = mv_multiply(mv_normalize(sphere[i].p[0]), radius);
		sphere[i].p[1] = mv_multiply(mv_normalize(sphere[i].p[1]), radius);
		sphere[i].p[2] = mv_multiply(mv_normalize(sphere[i].p[2]), radius);
		i++;
	}
}

void	set_sphere(t_tri *sphere, float radius)
{
	t_vector	v[12];

	setup_vectors(v);
	sphere[0] = (t_tri){{v[0], v[11], v[5]}};
	sphere[1] = (t_tri){{v[0], v[5], v[1]}};
	sphere[2] = (t_tri){{v[0], v[1], v[7]}};
	sphere[3] = (t_tri){{v[0], v[7], v[10]}};
	sphere[4] = (t_tri){{v[0], v[10], v[11]}};
	sphere[5] = (t_tri){{v[1], v[5], v[9]}};
	sphere[6] = (t_tri){{v[5], v[11], v[4]}};
	sphere[7] = (t_tri){{v[11], v[10], v[2]}};
	sphere[8] = (t_tri){{v[10], v[7], v[6]}};
	sphere[9] = (t_tri){{v[7], v[1], v[8]}};
	sphere[10] = (t_tri){{v[3], v[9], v[4]}};
	sphere[11] = (t_tri){{v[3], v[4], v[2]}};
	sphere[12] = (t_tri){{v[3], v[2], v[6]}};
	sphere[13] = (t_tri){{v[3], v[6], v[8]}};
	sphere[14] = (t_tri){{v[3], v[8], v[9]}};
	sphere[15] = (t_tri){{v[4], v[9], v[5]}};
	sphere[16] = (t_tri){{v[2], v[4], v[11]}};
	sphere[17] = (t_tri){{v[6], v[2], v[10]}};
	sphere[18] = (t_tri){{v[8], v[6], v[7]}};
	sphere[19] = (t_tri){{v[9], v[8], v[1]}};
	ft_printf("%f|%f|%f|%f\n", sphere[0].p[0].x, sphere[0].p[0].y, sphere[0].p[0].z, sphere[0].p[0].w);
	spherize(sphere, radius);
	ft_printf("%f|%f|%f|%f\n", sphere[0].p[0].x, sphere[0].p[0].y, sphere[0].p[0].z, sphere[0].p[0].w);
}