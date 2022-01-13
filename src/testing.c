#include "doom.h"

void	init_tests(t_doom *doom)
{
	doom->world.tricount = 12;
	//doom->world.tricount = 1; //TESTING
	doom->world.cube_rotation = (t_vector){1, 1, 1, 1};
	doom->world.camera = (t_vector){0, 0, 0, 1};
	doom->world.cam_fov = 90;
	doom->world.cam_distance = 4;
	doom->world.cube = (t_tri *)malloc(sizeof(t_tri) * doom->world.tricount);
	if (!doom->world.cube)
		ft_getout("failed to malloc cube!");
	//south
	doom->world.cube[0].p[0] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[0].p[1] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[0].p[2] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[1].p[0] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[1].p[1] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[1].p[2] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	//east
	doom->world.cube[2].p[0] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.cube[2].p[1] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	doom->world.cube[2].p[2] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[3].p[0] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.cube[3].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[3].p[2] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	//north
	doom->world.cube[4].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[4].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[4].p[2] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[5].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[5].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[5].p[2] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	//west
	doom->world.cube[6].p[0] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[6].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[6].p[2] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[7].p[0] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[7].p[1] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[7].p[2] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	//top
	doom->world.cube[8].p[0] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[8].p[1] = (t_vector){0.0f, 1.0f, 1.0f, 1};
	doom->world.cube[8].p[2] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[9].p[0] = (t_vector){0.0f, 1.0f, 0.0f, 1};
	doom->world.cube[9].p[1] = (t_vector){1.0f, 1.0f, 1.0f, 1};
	doom->world.cube[9].p[2] = (t_vector){1.0f, 1.0f, 0.0f, 1};
	//bottom
	doom->world.cube[10].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[10].p[1] = (t_vector){0.0f, 0.0f, 1.0f, 1};
	doom->world.cube[10].p[2] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[11].p[0] = (t_vector){1.0f, 0.0f, 1.0f, 1};
	doom->world.cube[11].p[1] = (t_vector){0.0f, 0.0f, 0.0f, 1};
	doom->world.cube[11].p[2] = (t_vector){1.0f, 0.0f, 0.0f, 1};
	doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
	(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
}

void	cleanup_tests(t_doom *doom)
{
	if (doom->world.cube)
		free(doom->world.cube);
}

void	dotests(t_doom *doom)
{
	r_dotests(doom);
}
