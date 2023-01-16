#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"

#define LEFT 1
#define RIGHT 2

class Entity
{
public:
	Entity(vector2f p_pos, SDL_Texture* p_tex, bool is_arrow, int player_direction);
	vector2f& getPos()
	{
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void move_entity(float speed);
private:
	vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	int textureWidth, textureHeight;
	int direction;
};