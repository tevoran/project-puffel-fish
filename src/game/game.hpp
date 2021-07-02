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
}
