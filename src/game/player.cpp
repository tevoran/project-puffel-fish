#include "game.hpp"

ppf::player::player(const char *path_to_player_sprite)
{
    xPos = 300;
    yPos = 0;
	m_player_sprite = new t3v::sprite(path_to_player_sprite);
	m_player_object.use_sprite(*m_player_sprite);
	m_player_object.position(xPos,yPos);
	m_player_object.scale(4); //is hardcoded, if this is changed, change it in game.hpp as well
}

ppf::player::~player()
{
	delete m_player_sprite;
}

void ppf::player::input()
{
	t3v::engine& te=t3v::engine::get();
	if(te.key_is_pressed(SDL_SCANCODE_SPACE))
	{
		yVel=-PLAYER_JUMP_SPEED;
	}
}

void ppf::player::gravity(float t_delta) {
	//applying gravity
    yVel+=GRAVITY*t_delta;

    //using new position
    xPos+=xVel*t_delta;
    yPos+=yVel*t_delta;

    //crashing on ground
    t3v::engine& te=t3v::engine::get();

    if(yPos>(te.get_resy()-PLAYER_SIZE))
    {
    	yPos=(te.get_resy()-PLAYER_SIZE);
    	yVel=0;
    }
    m_player_object.position(xPos, yPos);
}
