#pragma once

#include <te.hpp>
#include <chrono>
#include <ratio>

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
		float xPos=0;
		float yPos=0;
	public:
		player(const char *path_to_player_sprite);
		~player();

		void gravity();
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
