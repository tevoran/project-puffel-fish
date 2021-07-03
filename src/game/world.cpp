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
	tmp_bottom_element.xPos=te.get_resx()+rand()%(te.get_resx()/2);
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

	static float x_spawn=te.get_resx();

	//if first time period is over spawn new top hurdle
	static bool new_top_spawned=false;
	if(time_elapsed>HURDLE_SPAWN_SPEED && new_top_spawned==false)
	{
		new_top_spawned=true;
		ppf::world::world_element tmp_top_element;
		tmp_top_element.object=m_top_hurdle;
		tmp_top_element.xPos=x_spawn;;
		tmp_top_element.yPos=-WORLD_ELEMENT_SIZE_Y+rand()%WORLD_ELEMENT_SIZE_Y;
		tmp_top_element.xVel=-GAME_SPEED_HORIZONTAL;
		tmp_top_element.yVel=0;
		tmp_top_element.object.position(tmp_top_element.xPos, tmp_top_element.yPos);
		m_top.push_back(tmp_top_element);
	}
	//if the second time period is over then spawn a new bottom hurdle
	if(time_elapsed>(HURDLE_SPAWN_SPEED*2))
	{
		time_elapsed=0;
		new_top_spawned=false;

		ppf::world::world_element tmp_bottom_element;
		tmp_bottom_element.object=m_bottom_hurdle;
		tmp_bottom_element.xPos=x_spawn;
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
			bool is_done=false;
			x_spawn+=rand()%(te.get_resx()/4)+HURDLE_MIN_SPACE;
			while(!is_done)
			{
				m_top[i].xPos=x_spawn;
				m_top[i].yPos=-WORLD_ELEMENT_SIZE_Y+rand()%WORLD_ELEMENT_SIZE_Y;

				bool collision=false;
				//check for collision with bottom hurdles
				for(int j=0; j<m_bottom.size(); j++)
				{
					if(ppf::is_colliding(
						m_top[i].xPos,
						m_top[i].yPos,
						WORLD_ELEMENT_SIZE_X+HURDLE_MIN_SPACE,
						WORLD_ELEMENT_SIZE_Y+HURDLE_MIN_SPACE,
						m_bottom[j].xPos,
						m_bottom[j].yPos,
						WORLD_ELEMENT_SIZE_X+HURDLE_MIN_SPACE,
						WORLD_ELEMENT_SIZE_Y))
						{
							collision=true;
						}
				}
				if(collision==false)
				{
					is_done=true;
				}
				if(!is_done)
				{
					std::cout << "error1"  << std::endl;
				}
			}
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
			bool is_done=false;
			while(!is_done)
			{
				m_bottom[i].xPos=x_spawn;
				m_bottom[i].yPos=te.get_resy()-rand()%WORLD_ELEMENT_SIZE_Y;

				bool collision=false;
				//check for collision with bottom hurdles
				for(int j=0; j<m_bottom.size(); j++)
				{
					if(ppf::is_colliding(
						m_bottom[i].xPos,
						m_bottom[i].yPos,
						WORLD_ELEMENT_SIZE_X+HURDLE_MIN_SPACE,
						WORLD_ELEMENT_SIZE_Y,
						m_top[j].xPos,
						m_top[j].yPos,
						WORLD_ELEMENT_SIZE_X+HURDLE_MIN_SPACE,
						WORLD_ELEMENT_SIZE_Y))
						{
							collision=true;
						}
				}
				if(collision==false)
				{
					is_done=true;
				}
				if(!is_done)
				{
					std::cout << "error2"  << std::endl;
				}
			}
		}
	}
}