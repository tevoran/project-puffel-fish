#pragma once

#include <te.hpp>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <time.h>

//definitions
#define GRAVITY 200
#define PLAYER_SIZE 32*4
#define PLAYER_JUMP_SPEED 275

#define BACKGROUND_SPEED_HORIZONTAL 40
#define BUBBLE_COUNT 25

#define GAME_SPEED_HORIZONTAL 60
#define WORLD_ELEMENT_SIZE_X 32
#define WORLD_ELEMENT_SIZE_Y 512

namespace ppf
{
	class time
	{
	private:
		std::chrono::steady_clock::time_point t_old;
		std::chrono::steady_clock::time_point t_new;
		float t_delta_float;
	public:
		time();
		void update();
		float get_delta();
	};

	class player
	{
	private:
		t3v::object2d  m_player_object;
		t3v::sprite *m_player_sprite=NULL;

		//position
		float xPos=0;
		float yPos=0;

		//speed
		float xVel=0;
		float yVel=0;

	public:
		player(const char *path_to_player_sprite);
		~player();

		void input();
		void gravity(float t_delta);
		void render(){m_player_object.render();};
	};

	class world
	{
	private:
		struct world_element
		{
			t3v::object2d object;
			float xPos;
			float yPos;
			float xVel;
			float yVel;
			int xSize;
			int ySize;
		};

		//bottom
		t3v::object2d m_bottom_hurdle;
		t3v::sprite *m_bottom_hurdle_sprite=NULL;
		std::vector<world_element> m_bottom;

		//top
		t3v::object2d m_top_hurdle;
		t3v::sprite *m_top_hurdle_sprite=NULL;
		std::vector<world_element> m_top;

	public:
		world();
		~world();

		void render(float t_delta);
	};

	class background
	{
	private:
		struct bubble_struct
		{
			t3v::object2d object;
			float xPos;
			float yPos;
			float xVel=0;
			float yVel=0;
		};


		t3v::object2d m_bubble;
		t3v::sprite *m_bubble_sprite=NULL;

		std::vector<bubble_struct> bubbles;

	public:
		background();
		~background();

		void render(float t_delta);
	};
}
