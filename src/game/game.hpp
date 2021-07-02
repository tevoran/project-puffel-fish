#pragma once

#include <te.hpp>

namespace ppf
{
	class player
	{
	private:
		t3v::object2d  m_player_object;
		t3v::sprite *m_player_sprite=NULL;
	public:
		player(const char *path_to_player_sprite);
		~player();

		void render(){m_player_object.render();};
	};

	class world
	{
	private:
		t3v::object2d m_world_base_bottom_hurdle;
		t3v::sprite *m_world_base_bottom_hurdle_sprite=NULL;
	public:
		world();
		~world();

		void render();
	};
}
