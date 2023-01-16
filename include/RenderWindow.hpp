#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow{

public:
	RenderWindow(const  char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void clear();
	void render(Entity& p_entity);
	void renderPlayer(SDL_Texture* p_tex, SDL_Rect p_playerRect, SDL_Rect p_playerPosition);
	void renderScenario(SDL_Texture* p_tex);
	void renderArrow(SDL_Texture* p_tex, SDL_Rect p_arrowRect, float p_pos_x, float p_pos_y);
	SDL_Renderer* get_renderer()
	{
		return renderer;
	}
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenSurface;
};