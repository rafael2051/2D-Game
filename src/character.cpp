#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Character.hpp"
#include "Collision.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"
#define ARROW_UP SDL_SCANCODE_UP
#define ARROW_DOWN SDL_SCANCODE_DOWN
#define ARROW_LEFT SDL_SCANCODE_LEFT
#define ARROW_RIGHT SDL_SCANCODE_RIGHT
#define SPACE SDL_SCANCODE_SPACE
#define S SDL_SCANCODE_S

Player::Player(SDL_Texture* p_player_tex)
: player_tex(p_player_tex)
{
	SDL_QueryTexture(player_tex, NULL, NULL, &textureWidth, &textureHeight);
	
	player_direction = RIGHT;

	frameWidth = textureWidth / 13;

	frameHeight = textureHeight / 21;

	playerRect.x = 0;
	playerRect.y = frameHeight * 11;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	playerPosition.x = 0;
	playerPosition.y = 578;
	playerPosition.w = playerRect.w;
	playerPosition.h = playerRect.h;
}

int Player::check_keyState(const Uint8* p_keyState, std::vector <Entity> entitiees)
{
	if(p_keyState[ARROW_UP])
	{
		return 1;
	}
	else if(p_keyState[ARROW_DOWN])
	{
		return 2;
	}
	else if(p_keyState[SPACE])
	{
		return 3;
	}
	else if(p_keyState[S])
	{
		return 4;
	}
	else if(p_keyState[ARROW_LEFT])
	{
		direction(LEFT);
		collision.verify_collision_left(playerPosition, entitiees);
		if(!collision.get_collision_left())
			move_player_left();
		return 5;
	}
	else if(p_keyState[ARROW_RIGHT])
	{
		direction(RIGHT);
		collision.verify_collision_right(playerPosition, entitiees);
		if(!collision.get_collision_right())
			move_player_right();
		return 6;
	}
	else
	{
		stop_player();
	}
	return 0;
}

void Player::direction(int status)
{
	if(status == LEFT)
	{
		playerRect.y = frameHeight * 9;
		player_direction = LEFT;	
	}
	if(status == RIGHT)
	{
		playerRect.y = frameHeight * 11;
		player_direction = RIGHT;
	}
}

void Player::move_player_right()
{
	playerRect.x += frameWidth;
	playerPosition.x += 4;

	if(playerRect.x >= frameWidth * 9)
		playerRect.x = 0;

	print_position();
}
void Player::move_player_left()
{
		playerRect.x += frameWidth;
		playerPosition.x -= 4;

		if(playerRect.x >= frameWidth * 9)
			playerRect.x = 0;

		print_position();
}

void Player::jump_player_up(RenderWindow& window, std::vector<Entity> entitiees, SDL_Texture* scenario_texture)
{
	int i;

	if(player_direction == RIGHT)
		playerRect.y = frameHeight * 3;
	else
		playerRect.y = frameHeight * 1;

	for(i = 0;i < 7;i++)
	{
		playerRect.x += frameWidth;

		if(playerRect.x >= frameWidth * 7)
			playerRect.x = 0;

		playerPosition.y -= 18;

		if(i == 6)
			playerPosition.y -= 2;

		print_position();

		window.clear();
		window.renderScenario(scenario_texture);
		for(Entity& e : entitiees)
		{					
			window.render(e);	
		}
		window.renderPlayer(get_tex(), get_player(), get_position());
		window.display();
		SDL_Delay(60);
	}
}

void Player::jump_player_down(RenderWindow& window, std::vector<Entity> entitiees, SDL_Texture* scenario_texture)
{
	int i;

	if(player_direction == RIGHT)
		playerRect.y = frameHeight * 3;
	else
		playerRect.y = frameHeight * 1;

	for(i = 0;i < 7;i++)
	{
		playerRect.x += frameWidth;

		if(playerRect.x >= frameWidth * 7)
			playerRect.x = 0;

		playerPosition.y += 18;

		if(i == 6)
			playerPosition.y += 2;

		print_position();

		window.clear();
		window.renderScenario(scenario_texture);

		for(Entity& e : entitiees)
		{					
			window.render(e);	
		}

		window.renderPlayer(get_tex(), get_player(), get_position());
		window.display();
		SDL_Delay(60);
	}
}

void Player::jump_player_space(RenderWindow& window, std::vector<Entity> entitiees, SDL_Texture* scenario_texture, std::vector<Entity>& arrow_entitiees
							   , SDL_Texture* arrow_right)
{
	int i;

	for(i = 0;i < 50;i++)
	{

		if(player_direction == RIGHT)
			playerPosition.x += 3;
		else
			playerPosition.x -= 3;

		if(i < 25)
		{
			playerPosition.y -= 3;
			playerRect.x = frameHeight * 5;
		}
		else
		{
			playerPosition.y += 3;
			playerRect.x = frameHeight * 3;
		}

		print_position();

		window.clear();
		window.renderScenario(scenario_texture);
		for(Entity& e : entitiees)
		{					
			window.render(e);	
		}
		for(Entity& e : arrow_entitiees)
		{
			e.move_entity(6.0f);
			window.renderArrow(arrow_right, e.getCurrentFrame(),e.getPos().x, e.getPos().y);
		}
		window.renderPlayer(get_tex(), get_player(), get_position());
		window.display();
		SDL_Delay(10);
	}
}

void Player::shoot(RenderWindow& window, std::vector<Entity> entitiees, std::vector<Entity>& arrow_entitiees, SDL_Texture* scenario_texture, SDL_Texture* arrow_right)
{
	int i;
	if(player_direction == RIGHT)
		playerRect.y = frameHeight * 19;
	else
		playerRect.y = frameHeight * 17;
	playerRect.x = 0;
	for(i = 0; i < 10;i++)
	{
		window.clear();
		window.renderScenario(scenario_texture);
		for(Entity& e : entitiees)
		{					
			window.render(e);	
		}

		for(Entity& e : arrow_entitiees)
		{
			e.move_entity(5.4f);
			window.renderArrow(arrow_right, e.getCurrentFrame(),e.getPos().x, e.getPos().y);
		}

		window.renderPlayer(get_tex(), get_player(), get_position());
		window.display();
		if(i == 8)
		{
			for(int j = 0; j < 100; j++)
			{
				window.clear();
				window.renderScenario(scenario_texture);
				for(Entity& e : entitiees)
				{					
					window.render(e);	
				}

				for(Entity& e : arrow_entitiees)
				{
					e.move_entity(1.6f);
					window.renderArrow(arrow_right, e.getCurrentFrame(),e.getPos().x, e.getPos().y);
				}

				window.renderPlayer(get_tex(), get_player(), get_position());
				window.display();
				SDL_Delay(1);			
			}
		}
		SDL_Delay(10);
		playerRect.x += frameWidth;
		if(playerRect.x >= frameWidth * 10)
			playerRect.x = 0;
	}
}

void Player::stop_player()
{
	if(player_direction == RIGHT)
		playerRect.y = frameHeight * 11;
	else
		playerRect.y = frameHeight * 9;
	playerRect.x = 0;
}

void Player::print()
{
	std::cout << "Texture: " << textureWidth << ", " << textureHeight << std::endl;
	std::cout << "Player: " << playerRect.w << ", " << playerRect.h << std::endl;
	std::cout << "Player position: " << playerPosition.x << ", " << playerPosition.y << std::endl;
}