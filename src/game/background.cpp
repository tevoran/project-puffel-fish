#include "game.hpp"


ppf::background::background()
{
	m_bubble_sprite = new t3v::sprite("../assets/blase.bmp");
	m_bubble.use_sprite(*m_bubble_sprite);
	m_bubble.scale(2);

	t3v::engine& te=t3v::engine::get();

	bubble_struct tmp_bubble;
	tmp_bubble.yVel=rand()%40-70;
	tmp_bubble.xVel=-BACKGROUND_SPEED_HORIZONTAL;

	for(int i=0; i<BUBBLE_COUNT; i++)
	{
		tmp_bubble.object=m_bubble;
		tmp_bubble.yVel=rand()%65-70;
		tmp_bubble.xPos=rand()%te.get_resx();
		tmp_bubble.yPos=rand()%te.get_resy();

		bubbles.push_back(tmp_bubble);
		bubbles[i].object.position(bubbles[i].xPos, bubbles[i].yPos);
	}
}

ppf::background::~background()
{
	delete m_bubble_sprite;
}

void ppf::background::render(float t_delta)
{
	t3v::engine& te=t3v::engine::get();

	for(int i=0; i<BUBBLE_COUNT; i++)
	{
		//update location
		bubbles[i].xPos+=bubbles[i].xVel*t_delta;
		bubbles[i].yPos+=bubbles[i].yVel*t_delta;
		bubbles[i].object.position(bubbles[i].xPos, bubbles[i].yPos);

		if(bubbles[i].yPos<-PLAYER_SIZE)
		{
			bubbles[i].yVel=rand()%65-70;
			bubbles[i].xPos=rand()%(te.get_resx())+(te.get_resx()/4);
			bubbles[i].yPos=rand()%(te.get_resy()/2)+(te.get_resy()/2);
		}

		if(bubbles[i].xPos<-PLAYER_SIZE)
		{
			bubbles[i].yVel=rand()%65-70;
			bubbles[i].xPos=rand()%(te.get_resx())+(te.get_resx()/4);
			bubbles[i].yPos=rand()%(te.get_resy()/2)+(te.get_resy()/2);
		}

		//render
		bubbles[i].object.render();
	}
}