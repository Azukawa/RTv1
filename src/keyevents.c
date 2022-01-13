#include "doom.h"

static void projection_events(t_doom *doom, SDL_Event *e)
{
	if (e->window.event == SDL_WINDOWEVENT_CLOSE)
		doom->rend.run = FALSE;
	if (e->key.keysym.sym == SDLK_q && doom->world.cam_fov > 1)
	{
		doom->world.cam_fov--;
		doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
		(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
	}
	if (e->key.keysym.sym == SDLK_e && doom->world.cam_fov < 180)
	{
		doom->world.cam_fov++;
		doom->world.m_proj = mm_init_3d_projection(doom->world.cam_fov, \
		(float)WIN_H / (float)WIN_W, 0.1f, 1000.f);
	}
	if (e->key.keysym.sym == SDLK_UP)
		doom->world.cam_distance += 0.1f;
	if (e->key.keysym.sym == SDLK_DOWN && doom->world.cam_distance > 1.0f)
		doom->world.cam_distance -= 0.1f;
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_r)
	{
		if (doom->keys.rot_switch == TRUE)
			doom->keys.rot_switch = FALSE;
		else
			doom->keys.rot_switch = TRUE;
	}
}

void	keyevent(t_doom *doom, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		projection_events(doom, e);
		if (e->window.event == SDL_WINDOWEVENT_CLOSE)
			doom->rend.run = FALSE;
		if (e->key.keysym.sym == SDLK_UP)
			doom->keys.up_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_DOWN)
			doom->keys.down_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_LEFT)
			doom->keys.left_pressed = e->type == SDL_KEYDOWN;
		if (e->key.keysym.sym == SDLK_RIGHT)
			doom->keys.right_pressed = e->type == SDL_KEYDOWN;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_m) //mouse_swich
		{
			ft_printf("CLICK\n");
			if (doom->keys.mouse_switch == FALSE)
				doom->keys.mouse_switch = TRUE;
			else
				doom->keys.mouse_switch = FALSE;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_t) //fps_swich
		{
			ft_printf("CLICK\n");
			if(doom->keys.fps_switch == FALSE)
				doom->keys.fps_switch = TRUE;
			else
				doom->keys.fps_switch = FALSE;
		}
	}
}
