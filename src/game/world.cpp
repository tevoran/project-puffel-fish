#include "game.hpp"

ppf::world::world()
{
	t3v::engine& te=t3v::engine::get();

	//bottom
	m_bottom_hurdle_sprite=new t3v::sprite("../assets/AlgeGross.png");
	m_bottom_hurdle.use_sprite(*m_bottom_hurdle_sprite);

	//top
	m_top_hurdle_sprite=new t3v::sprite("../assets/Anker.png");
	m_top_hurdle.use_sprite(*m_top_hurdle_sprite);


	//creating hurdles
	//top
	ppf::world::world_element tmp_top_element;
	tmp_top_element.object=m_top_hurdle;
	tmp_top_element.xPos=te.get_resx()/2+rand()%(te.get_resx()/2);
	tmp_top_element.yPos=-WORLD_ELEMENT_SIZE_Y+rand()%WORLD_ELEMENT_SIZE_Y;
	tmp_top_element.xVel=-GAME_SPEED_HORIZONTAL;
	tmp_top_element.yVel=0;
	tmp_top_element.object.position(tmp_top_element.xPos, tmp_top_element.yPos);
	m_top.push_back(tmp_top_element);

	//bottom
	ppf::world::world_element tmp_bottom_element;
	tmp_bottom_element.object=m_bottom_hurdle;
	tmp_bottom_element.xPos=te.get_resx()/2+rand()%(te.get_resx()/2);
	tmp_bottom_element.yPos=te.get_resy()-rand()%WORLD_ELEMENT_SIZE_Y;
	tmp_bottom_element.xVel=-GAME_SPEED_HORIZONTAL;
	tmp_bottom_element.yVel=0;
	tmp_bottom_element.object.position(tmp_bottom_element.xPos, tmp_bottom_element.yPos);
	m_bottom.push_back(tmp_bottom_element);
}

ppf::world::~world()
{
	delete m_bottom_hurdle_sprite;
	delete m_top_hurdle_sprite;
}

void ppf::world::render(float t_delta)
{
	t3v::engine& te=t3v::engine::get();
	static float time_elapsed=0;
	time_elapsed+=t_delta;

	//if first time period is over spawn new top hurdle
	static bool new_top_spawned=false;
	if(time_elapsed>30 && new_top_spawned==false)
	{
		new_top_spawned=true;
		ppf::world::world_element tmp_top_element;
		tmp_top_element.object=m_top_hurdle;
		tmp_top_element.xPos=te.get_resx()+rand()%(te.get_resx()/2);
		tmp_top_element.yPos=-WORLD_ELEMENT_SIZE_Y+rand()%WORLD_ELEMENT_SIZE_Y;
		tmp_top_element.xVel=-GAME_SPEED_HORIZONTAL;
		tmp_top_element.yVel=0;
		tmp_top_element.object.position(tmp_top_element.xPos, tmp_top_element.yPos);
		m_top.push_back(tmp_top_element);
	}
	//if the second time period is over then spawn a new bottom hurdle
	if(time_elapsed>60)
	{
		time_elapsed=0;
		new_top_spawned=false;

		ppf::world::world_element tmp_bottom_element;
		tmp_bottom_element.object=m_bottom_hurdle;
		tmp_bottom_element.xPos=te.get_resx()+rand()%(te.get_resx()/2);
		tmp_bottom_element.yPos=te.get_resy()-rand()%WORLD_ELEMENT_SIZE_Y;
		tmp_bottom_element.xVel=-GAME_SPEED_HORIZONTAL;
		tmp_bottom_element.yVel=0;
		tmp_bottom_element.object.position(tmp_bottom_element.xPos, tmp_bottom_element.yPos);
		m_bottom.push_back(tmp_bottom_element);
	}

	//updating and render world elements
	//top
	for(int i=0; i<m_top.size(); i++)
	{	
		m_top[i].xPos+=m_top[i].xVel*t_delta;
		m_top[i].yPos+=m_top[i].yVel*t_delta;
		m_top[i].object.position(m_top[i].xPos, m_top[i].yPos);
		m_top[i].object.render();

		//respawn
		if(m_top[i].xPos<-WORLD_ELEMENT_SIZE_X)
		{
			m_top[i].xPos=te.get_resx()+rand()%(te.get_resx());
			m_top[i].yPos=-WORLD_ELEMENT_SIZE_Y+rand()%WORLD_ELEMENT_SIZE_Y;
		}
	}

	//bottom
	for(int i=0; i<m_bottom.size(); i++)
	{	
		m_bottom[i].xPos+=m_bottom[i].xVel*t_delta;
		m_bottom[i].yPos+=m_bottom[i].yVel*t_delta;
		m_bottom[i].object.position(m_bottom[i].xPos, m_bottom[i].yPos);
		m_bottom[i].object.render();

		//respawn
		if(m_bottom[i].xPos<-WORLD_ELEMENT_SIZE_X)
		{
			m_bottom[i].xPos=te.get_resx()+rand()%(te.get_resx());
			m_bottom[i].yPos=te.get_resy()-rand()%WORLD_ELEMENT_SIZE_Y;
		}
	}
}