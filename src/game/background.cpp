#include "game.hpp"

ppf::background::background()
{
	m_bubble_sprite = new t3v::sprite("../assets/blase.bmp");
	m_bubble.use_sprite(*m_bubble_sprite);
	m_bubble.position(300, 500);
	m_bubble.scale(2);
}

ppf::background::~background()
{
	delete m_bubble_sprite;
}

void ppf::background::render()
{
	m_bubble.render();
}