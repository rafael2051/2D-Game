#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(vector2f p_pos, SDL_Texture* p_tex, bool is_arrow, int player_direction)

:pos(p_pos), tex(p_tex)

{
	SDL_QueryTexture(p_tex, NULL, NULL, &textureWidth, &textureHeight);
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = textureWidth;
	currentFrame.h = textureHeight;
	if(is_arrow)
	{
		currentFrame.w = textureWidth/2;
		direction = player_direction;
		if(player_direction == RIGHT)
			currentFrame.x = 0;
		else
			currentFrame.x = 28;
	}
}

SDL_Texture* Entity::getTex()
{
	return tex;
}


SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::move_entity(float speed)
{
	if(direction == LEFT && pos.x > -28 && pos.x < 1280)
	{
		pos.x -= speed;
	}
	if(direction == RIGHT && pos.x < 1280 && pos.x > -28)
	{
		pos.x += speed;
	}
}