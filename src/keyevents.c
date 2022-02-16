#include "doom.h"

void	keyevent(t_doom *doom, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
	//	printf("keyevent = %i\n", e->key.keysym.sym);

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
		if (e->key.keysym.sym == 1073741916)
			doom->xvar -= 1;
		if (e->key.keysym.sym == 1073741918)
			doom->xvar += 1;
		if (e->key.keysym.sym == 1073741920)
			doom->yvar -= 1;
		if (e->key.keysym.sym == 1073741914)
			doom->yvar += 1;
		if (e->key.keysym.sym == 1073741919)
			doom->zvar += 1;
		if (e->key.keysym.sym == 1073741913)
			doom->zvar -= 1;


	}
	
}
