#pragma once

#include <te.hpp>
#include <chrono>
#include <ratio>

//definitions
#define GRAVITY 200
#define PLAYER_SIZE 32*4


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

		void gravity(float t_delta);
		void render(){m_player_object.render();};
	};

	class world
	{
	private:
		//bottom
		t3v::object2d m_bottom_hurdle;
		t3v::sprite *m_bottom_hurdle_sprite=NULL;

		//top
		t3v::object2d m_top_hurdle;
		t3v::sprite *m_top_hurdle_sprite=NULL;
	public:
		world();
		~world();

		void render();
	};
}
