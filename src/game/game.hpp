#pragma once

#include <te.hpp>

namespace ppf
{
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
