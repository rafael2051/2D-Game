#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Collision.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"

#define RIGHT 2
#define LEFT 1

class Player{
public:
	Player(SDL_Texture* p_player_tex);
	SDL_Texture* get_tex()
	{
		return player_tex;
	}

	SDL_Rect get_player()
	{
		return playerRect;
	}

	SDL_Rect get_position()
	{
		return playerPosition;
	}

	int get_direction()
	{
		return player_direction;
	}

	int check_keyState(const Uint8* p_keyState, std::vector<Entity> p_entitiees);

	void direction(int status);

	void move_player_right();

	void move_player_left();

	void jump_player_up(RenderWindow& window, std::vector<Entity> entitiees,SDL_Texture* scenario_texture);

	void jump_player_down(RenderWindow& window, std::vector<Entity> entitiees, SDL_Texture* scenario_texture);

	void jump_player_space(RenderWindow& window, std::vector<Entity> entitiees, SDL_Texture* scenario_texture, std::vector<Entity>& arrow_entitiees,
						   SDL_Texture * arrow_right);

	void shoot(RenderWindow& window, std::vector<Entity> entitiees, std::vector<Entity>& arrow_entitiees, SDL_Texture* scenario_texture, 
			   SDL_Texture* arrow_right);

	void stop_player();

	void print();

	void print_position() {std::cout << "Player position: x: " << playerPosition.x << ", y: "<< playerPosition.y << std::endl;}

private:
		SDL_Texture* player_tex;
		int player_direction;
		int textureWidth, textureHeight;
		int frameWidth, frameHeight;
		SDL_Rect playerRect;
		SDL_Rect playerPosition;
		Collision collision;
};