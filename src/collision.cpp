#include <SDL2/SDL.h>
#include "Entity.hpp"
#include "Collision.hpp"
#include <vector>

void Collision::verify_collision_right(SDL_Rect p_position, std::vector<Entity> p_entitiees)
{
	collision_right = false;
	for(Entity e : p_entitiees)
	{

		if(e.getPos().y == p_position.y - 66)
		{
			
			//std::cout << e.getPos().x << ", " << e.getPos().y << std::endl;

			if( (p_position.x - 20) + p_position.w >= e.getPos().x 
				&&p_position.x + 40 <= e.getPos().x + (e.getCurrentFrame().w * 4))
			{
				std::cout << "Collision dettected." << p_position.x << std::endl;
				collision_right = true;
			}

		}

	}

}

void Collision::verify_collision_left(SDL_Rect p_position, std::vector<Entity> p_entitiees)
{
	collision_left = false;

	for(Entity e : p_entitiees)
	{

		if(e.getPos().y == p_position.y - 66)
		{
			
			//std::cout << e.getPos().x << ", " << e.getPos().y << std::endl;

			if( (p_position.x + 20) <= e.getPos().x + (e.getCurrentFrame().w * 4)
			    && (p_position.x - 40) + p_position.w >= e.getPos().x)
			{
				std::cout << "Collision dettected." << p_position.x << std::endl;
				collision_left = true;
			}

		}

	}

}