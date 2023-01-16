#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if(window == NULL)
	{

		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
	screenSurface = SDL_GetWindowSurface(window);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{

	SDL_Texture* texture = NULL;

	texture = IMG_LoadTexture(renderer, p_filePath);
	if(texture == NULL)

	{

		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	}

	return texture;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{

	SDL_Rect src;

	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dest;

	dest.x = p_entity.getPos().x;
	dest.y = p_entity.getPos().y;
	dest.w = p_entity.getCurrentFrame().w * 4;
	dest.h = p_entity.getCurrentFrame().h * 4;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dest);
}

void RenderWindow::renderPlayer(SDL_Texture* p_tex, SDL_Rect p_playerRect, SDL_Rect p_playerPosition)
{
	SDL_RenderCopy(renderer, p_tex, &p_playerRect, &p_playerPosition);
}

void RenderWindow::renderScenario(SDL_Texture* p_tex)
{
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::renderArrow(SDL_Texture* p_tex, SDL_Rect p_arrowRect, float p_pos_x, float p_pos_y)
{
	SDL_Rect arrowPosition;
	arrowPosition.x = p_pos_x;
	arrowPosition.y = p_pos_y;
	arrowPosition.w = p_arrowRect.w;
	arrowPosition.h = p_arrowRect.h;
	SDL_RenderCopy(renderer, p_tex, &p_arrowRect, &arrowPosition);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}


 void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}