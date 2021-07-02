#include "game.hpp"

ppf::world::world()
{
	m_world_base_bottom_hurdle_sprite=new t3v::sprite("../assets/bottom_hurdle.bmp");
	m_world_base_bottom_hurdle.use_sprite(*m_world_base_bottom_hurdle_sprite);
	m_world_base_bottom_hurdle.position(500, 600);
}

ppf::world::~world()
{
	delete m_world_base_bottom_hurdle_sprite;
}

void ppf::world::render()
{
	m_world_base_bottom_hurdle.render();
}