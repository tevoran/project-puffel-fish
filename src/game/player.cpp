#include "game.hpp"

ppf::player::player(const char *path_to_player_sprite_small, const char *path_to_player_sprite_big)
{
    xPos = 300;
    yPos = 0;
	m_player_sprite_small = new t3v::sprite(path_to_player_sprite_small);
    m_player_sprite_big = new t3v::sprite(path_to_player_sprite_big);
	m_player_object.use_sprite(*m_player_sprite_small);
	m_player_object.position(xPos,yPos);
	m_player_object.scale(SCALE_SMALL); //is hardcoded, if this is changed, change it in game.hpp as well
	isSmall = true;
}

ppf::player::~player()
{
	delete m_player_sprite_small;
	delete m_player_sprite_big;
}

void ppf::player::input()
{
	t3v::engine& te=t3v::engine::get();
	if(te.key_is_pressed(SDL_SCANCODE_SPACE) && yVel>=0)
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

float ppf::player::getHp() const {
    return hp;
}

void ppf::player::damage(float pDamage) {
    hp -= pDamage;
}

bool ppf::player::takesDamage(ppf::world &pWorld) const {
    //check if fish leaves water
    if(yPos < -PLAYER_SIZE_Y)
        return true;

    if(takesDamageSmall(pWorld) && isSmall)
        return true;

    if(takesDamageBig(pWorld) && !isSmall)
        return true;

    return false;
}

bool ppf::player::takesDamageSmall(ppf::world &pWorld) const {
    //check with top objects
    for(int i; i < pWorld.getMTop().size(); i++){
        if(ppf::is_colliding(xPos + PLAYER_SIZE_X/2, yPos + PLAYER_SIZE_Y/2, PLAYER_SIZE_X, PLAYER_SIZE_Y,
                             pWorld.getMTop().at(i).xPos,pWorld.getMTop().at(i).yPos,
                             WORLD_ELEMENT_SIZE_X, WORLD_ELEMENT_SIZE_Y))
            return true;
    }

    //check with bottom objects
    for(int i; i < pWorld.getMBottom().size(); i++) {
        if (ppf::is_colliding(xPos + PLAYER_SIZE_X, yPos + PLAYER_SIZE_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y,
                              pWorld.getMBottom().at(i).xPos, pWorld.getMBottom().at(i).yPos,
                              WORLD_ELEMENT_SIZE_X, WORLD_ELEMENT_SIZE_Y))
            return true;
    }

    return false;
}

bool ppf::player::takesDamageBig(ppf::world &pWorld) const{
    //check with top objects
    for(int i; i < pWorld.getMTop().size(); i++){
        if(ppf::is_colliding(xPos + PLAYER_SIZE_X, yPos + PLAYER_SIZE_Y, PLAYER_SIZE_X*4, PLAYER_SIZE_Y*4,
                             pWorld.getMTop().at(i).xPos,pWorld.getMTop().at(i).yPos,
                             WORLD_ELEMENT_SIZE_X, WORLD_ELEMENT_SIZE_Y))
            return true;
    }

    //check with bottom objects
    for(int i; i < pWorld.getMBottom().size(); i++){
        if(ppf::is_colliding(xPos + PLAYER_SIZE_X, yPos + PLAYER_SIZE_Y, PLAYER_SIZE_X*4, PLAYER_SIZE_Y*4,
                             pWorld.getMBottom().at(i).xPos, pWorld.getMBottom().at(i).yPos,
                             WORLD_ELEMENT_SIZE_X, WORLD_ELEMENT_SIZE_Y))
            return true;
    }

    return false;
}



void ppf::player::toggleSize() {
    if(isSmall){
        m_player_object.use_sprite(*m_player_sprite_big);
        m_player_object.scale(SCALE_BIG);
        isSmall = false;
    }
    else{
        m_player_object.use_sprite(*m_player_sprite_small);
        m_player_object.scale(SCALE_SMALL);
        isSmall = true;
    }
}



