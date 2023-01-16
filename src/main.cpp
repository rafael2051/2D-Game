#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include <stdlib.h>
#include <time.h>
#include "Entity.hpp"
#include "Math.hpp"
#include "Character.hpp"
#include "Collision.hpp"
#define FALSE 0
#define TRUE 1

enum KEYS
{
	UP = 1,
	DOWN,
	SPACE,
	S
};

//All the comments in this code will be both in english and portuguese(my native language).
//Todos os comentários nesse código serão tanto em inglês quanto em português(minha linguagem nativa).
int main(int agrc, char * argv[])
{

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
	{
		std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
		return 1;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Can't open audio. Error: " << Mix_GetError() << std::endl;
		return 1;
	}

	else
	{

		if( ! (IMG_Init(IMG_INIT_PNG)) )
		{
			std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return 1;
		}

		//If all the initializations was succesful, game will start.
		//Se todas incializações foram bem sucedidas, o jogo vai iniciar.
		else
		{

			std::cout << "Initialization was succesful" << std::endl;
			//frameTime is the time in which every frame will be updated. prevTime and currentTime will
			//be used to count the amount of time passed since the last loap in the main while using the
			//SDL_GetTicks function. deltaTime will be the difference between currentTime and prevTime,
			//that represents the time passed since the last loap, and in every interaction in the loap
			//frameTime will be updated with deltaTime. When frameTime reach certain value, then the
			//frame will be updated.
			//frameTime é o tempo para cada atualização de frame. prevTime e currentTime serão usados para
			//contar a quantidade de tempo desde o último loap do while principal usando a função SDL_GetTicks.
			//deltaTime será a diferença entre currentTime e prevTime, que representa a quantidade de tempo
			//desde o último loap, e em cada iteração do laço frameTime será atualizado com deltaTime. Quando
			//frameTime alcançar um determinado valor, o frame será atualizado.
			int i, cont, status;
			float frameTime = 0;
			float frameTimeArrow = 0;
			int prevTime = 0;
			int currentTime = 0;
			float deltaTime = 0;
			const Uint8* keyState;

			//If collision is true, the character will not walk. If there is no ground, character will fall.
			//Se o valor de collision é true, o personagem não vai andar. Isso quer dizer que há um obstáculo
			//a frente. Se não há chão abaixo do personagem, o valor de ground será atualizado para false e 
			//o personagem vai cair.


			RenderWindow window("GAME.v1.0", 1280, 769);
			SDL_Texture* grassTexture = window.loadTexture("res\\gfx\\Ground_Grass\\ground_grass_2.png");
			SDL_Texture* player_texture = window.loadTexture("res\\gfx\\player.png");
			SDL_Texture* scenario_texture = window.loadTexture("res\\gfx\\Scenarios\\scenario_4.png");
			SDL_Surface* arrow_right_surface = SDL_LoadBMP("res\\gfx\\arrow.bmp");
			SDL_SetColorKey(arrow_right_surface, SDL_TRUE, SDL_MapRGB(arrow_right_surface->format, 0, 0, 0));
			SDL_Texture* arrow_right = SDL_CreateTextureFromSurface(window.get_renderer(), arrow_right_surface);

			std::vector<Entity> arrow_entitiees;


			Mix_Chunk* soundtrack = Mix_LoadWAV("res\\Music\\Soundtrack_3.mp3");
			Mix_Chunk* arrow_sound = Mix_LoadWAV("res\\Sound effect\\arrow.mp3");
			Mix_Music* background_sound = Mix_LoadMUS("res\\Background sound\\Background_sound_2.mp3");

			if(soundtrack == NULL || background_sound == NULL || arrow_sound == NULL)
			{
				std::cout << "Failed to load music. Error: " << SDL_GetError() << std::endl;
			}

			Player player(player_texture);
			player.print();
			float x, y;
			int t_x, t_y;

			//srand is used so all platforms will be showed in screen in random positions.
			//srand é usado para aleatorizar a posição de cada plataforma.
			srand(time(NULL));

			//Entity entities[4] = {Entity(0, 613, grassTexture),
			//					    Entity(128, 613, grassTexture),
			//					    Entity(256, 613, grassTexture),
			//					    Entity(374, 613, grassTexture)};

			//Dynamic vector that will contain every entity with a random position.
			//Vetor dinâmico que conterá toda entity com uma posição aleatória.
			std::vector<Entity> entitiees;

			//The first entity, that will no be random. This assure that the player will not
			//begin the game without a platform beneath him.
			//A primeira entity, que não será aleatória. Isso garante que o jogador não começará
			//o jogo sem uma plataforma abaixo dele.
			{
				vector2f pos(0, 640);
				std::cout << "Player platform: pos: 0, 640" << std::endl; 
				Entity newEntity(pos, grassTexture, FALSE, 0);
				entitiees.push_back(newEntity);
			}

			//This for will generate 10 entities with a random position on the window, since the for
			//will interact 10 times. But the y position is not randomized in this case, all the entities
			//in this case will be in the ground, but their x position will be random.
			//Esse for vai gerar 10 entities com uma posição aleatória na janela, já que o for vai interagir
			//10 vezes. Mas a posição do eixo y não será aleatorizada nesse caso, todas as entities vão estar no chão,
			//mas a posição do eixo x será aleatória.
			for(i = 0, y = 640, cont = 1;i < 10; i++, cont++)
			{
				t_x = (rand() % 1152);
				while((t_x % 128) != 0)
				{
					if(t_x < 1024)
						t_x--;
					else
						t_x++;
				}
				x = (float) t_x;
				std::cout << "Platform " << cont << ": pos: " << x << ", " << y << std::endl;				
				vector2f pos(x, y);
				Entity newEntity(pos, grassTexture, FALSE, 0);
				entitiees.push_back(newEntity);
			}

			for(i = 0; i < 20;i++, cont++)
			{
				t_x = (rand() % 1152);
				while((t_x % 128) != 0)
				{
					if(t_x < 1024)
						t_x--;
					else
						t_x++;
				}
				t_y = (rand() % 641);
				while((t_y % 128) != 0)
				{
					if(t_y < 512)
						t_y--;
					else
					{
						t_y = 512;
						break;
					}
				}
				if(t_x == 0 && t_y == 512)
					t_x = 128;
				x = (float) t_x;
				y = (float) t_y;
				std::cout << "Platform "<< cont << ": " << x << ", " << y << std::endl;
				vector2f pos(x, y);
				Entity newEntity(pos, grassTexture, FALSE, 0);
				entitiees.push_back(newEntity);
			}

			bool gameRunning = true;

			SDL_Event event;

			Mix_PlayChannel(0, soundtrack, -1);
			Mix_PlayMusic(background_sound, -1);

			//for(i = 1; i < 200;i++)
			//{
			//	for(int j = 1; j < i;j++)
			//	{
			//		if(3*i == 4*j)
			//			std::cout << "3 * " << i << " = 4 * " << j << std::endl;
			//	}
			//}

			while(gameRunning)
			{
				prevTime = currentTime;
				currentTime = SDL_GetTicks();
				deltaTime = (currentTime - prevTime) / 1000.0f;
				frameTime += deltaTime;
				frameTimeArrow += deltaTime;

				while(SDL_PollEvent(&event))
				{
					if(event.type == SDL_QUIT)
						gameRunning = false;
				}

				keyState = SDL_GetKeyboardState(NULL);

				if(frameTime >= 0.04f)
				{
					frameTime = 0;
					if( (status = player.check_keyState(keyState, entitiees)) )
					switch(status)
					{
						case UP: player.jump_player_up(window, entitiees, scenario_texture); break;
						case DOWN: player.jump_player_down(window, entitiees, scenario_texture); break;
						case SPACE: player.jump_player_space(window, entitiees, scenario_texture, arrow_entitiees, arrow_right); break;
						case S: if(frameTimeArrow >= 1.0f)
								{
								frameTimeArrow = 0; Mix_PlayChannel(1, arrow_sound, 0); player.shoot(window, entitiees, arrow_entitiees, scenario_texture, arrow_right);
								vector2f pos_arrow(player.get_position().x + 40, player.get_position().y + 30);
								Entity new_entity_arrow(pos_arrow, arrow_right, TRUE, player.get_direction()); arrow_entitiees.push_back(new_entity_arrow); break;
								}
					}
				}

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

				SDL_Delay(10);
					
				window.renderPlayer(player.get_tex(), player.get_player(), player.get_position());

				window.display();

			}
			window.cleanUp();

			Mix_FreeMusic(background_sound);

			soundtrack = NULL;
			Mix_Quit();
			SDL_Quit();
		}
	}
	return 0;
}