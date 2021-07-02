#include "game.hpp"

ppf::player::player(const char *path_to_player_sprite)
{
	m_player_sprite = new t3v::sprite(path_to_player_sprite);
	m_player_object.use_sprite(*m_player_sprite);
	m_player_object.scale(4);
}

ppf::player::~player()
{
	delete m_player_sprite;
}