#include "doom.h"

t_quad	*init_cube(void)
{
	t_quad	*cube;

	cube = (t_quad *)malloc(sizeof(t_quad) * 6);
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
	c[0].p[0] = (t_vector){p.x, p.y, p.z, 1};
	c[0].p[1] = (t_vector){p.x, (p.y + d.y), p.z, 1};
	c[0].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1};
	c[0].p[3] = (t_vector){(p.x + d.x), p.y, p.z, 1};
	c[1].p[0] = (t_vector){(p.x + d.x), p.y, p.z, 1};
	c[1].p[1] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1};
	c[1].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1};
	c[1].p[3] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1};
	c[2].p[0] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1};
	c[2].p[1] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1};
	c[2].p[2] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1};
	c[2].p[3] = (t_vector){p.x, p.y, (p.z + d.z), 1};
	c[3].p[0] = (t_vector){p.x, p.y, (p.z + d.z), 1};
	c[3].p[1] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1};
	c[3].p[2] = (t_vector){p.x, (p.y + d.y), p.z, 1};
	c[3].p[3] = (t_vector){p.x, p.y, p.z, 1};
	c[4].p[0] = (t_vector){p.x, (p.y + d.y), p.z, 1};
	c[4].p[1] = (t_vector){p.x, (p.y + d.y), (p.z + d.z), 1};
	c[4].p[2] = (t_vector){(p.x + d.x), (p.y + d.y), (p.z + d.z), 1};
	c[4].p[3] = (t_vector){(p.x + d.x), (p.y + d.y), p.z, 1};
	c[5].p[0] = (t_vector){(p.x + d.x), p.y, (p.z + d.z), 1};
	c[5].p[1] = (t_vector){p.x, p.y, (p.z + d.z), 1};
	c[5].p[2] = (t_vector){p.x, p.y, p.z, 1};
	c[5].p[3] = (t_vector){(p.x + d.x), p.y, p.z, 1};
}