#include "main.h"

t_game	*game_init()
{
	t_game	*game;

	game = xcalloc(1, sizeof(t_game));
	game->character = character_init();
	game->map = map_from_string(readfile("map.txt"), game->character);
	game->window = create_window();
	game->screen = SDL_GetWindowSurface(game->window);
	game->state = GAME_MENU;
	return game;
}

t_tick g_tick_fns[] = {
	{GAME_MENU, tick_game_menu},
	{CLASS_MENU, tick_class_menu},
	{MAP, tick_map},
	{MAP_MENU, tick_map_menu},
	{FIGHT, tick_fight}
};

void	game_tick(t_game *game)
{
	int	i;

	for (i = 0; i < NUM_STATES; ++i)
	{
		if (g_tick_fns[i].state == game->state)
		{
			g_tick_fns[i].fn(game);
			xupdate_window_surface(game->window);
			return;
		}
	}
	err("Game got into corrupted state. Aborting ...");
}

void	game_quit(t_game *game)
{
	SDL_DestroyWindow(game->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}