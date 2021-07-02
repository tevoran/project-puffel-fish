#include "game.hpp"

ppf::world::world()
{
	//bottom
	m_bottom_hurdle_sprite=new t3v::sprite("../assets/bottom_hurdle.bmp");
	m_bottom_hurdle.use_sprite(*m_bottom_hurdle_sprite);
	m_bottom_hurdle.position(500, 600);
	m_bottom_hurdle.scale(1.6);



	//top
	m_top_hurdle_sprite=new t3v::sprite("../assets/bottom_top.bmp");
	m_top_hurdle.use_sprite(*m_top_hurdle_sprite);
	m_top_hurdle.position(600, 0);
	m_top_hurdle.scale(1.6);
}

ppf::world::~world()
{
	delete m_bottom_hurdle_sprite;
	delete m_top_hurdle_sprite;
}

void ppf::world::render()
{
	m_bottom_hurdle.render();
	m_top_hurdle.render();

}