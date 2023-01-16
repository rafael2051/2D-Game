#pragma once

#include <SDL2/SDL.h>
#include "Entity.hpp"
#include <vector>

class Collision
{
public:
	Collision(){collision_right = collision_left = false;}
	bool get_collision_right()
	{
		return collision_right;
	}
	bool get_collision_left()
	{
		return collision_left;
	}
	void verify_collision_right(SDL_Rect p_position, std::vector<Entity> p_entitiees);

	void verify_collision_left(SDL_Rect p_position, std::vector<Entity> p_entitiees);

private:
	bool collision_right;
	bool collision_left;
};