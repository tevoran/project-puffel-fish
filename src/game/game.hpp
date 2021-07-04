#pragma once

#include <te.hpp>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <time.h>

//definitions
#define GRAVITY 200
#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 32
#define PLAYER_SIZE 32*5
#define PLAYER_JUMP_SPEED 275
#define PLAYER_DAMAGE_SPEED 30
#define PLAYER_POINTS_SMALL_SPEED 10
#define PLAYER_POINTS_BIG_SPEED 30

#define BACKGROUND_SPEED_HORIZONTAL 40
#define BUBBLE_COUNT 25

#define GAME_SPEED_HORIZONTAL 125
#define WORLD_ELEMENT_SIZE_X 32
#define WORLD_ELEMENT_SIZE_Y 512
#define HURDLE_MIN_SPACE 250
#define HURDLE_SPAWN_SPEED 5

#define SCALE_SMALL 3
#define SCALE_BIG 5


namespace ppf
{
	class time
	{
	private:
		std::chrono::steady_clock::time_point t_old;
		std::chrono::steady_clock::time_point t_new;
		float t_delta_float;
	public:
		time();
		void update();
		float get_delta();
	};

    class world
    {
    private:
        struct world_element
        {
            t3v::object2d object;
            float xPos;
            float yPos;
            float xVel;
            float yVel;
            int xSize;
            int ySize;
        };

        //bottom
        t3v::object2d m_bottom_hurdle;
        t3v::sprite *m_bottom_hurdle_sprite=NULL;
        std::vector<world_element> m_bottom;
    public:
        const std::vector<world_element> &getMBottom() const;

        const std::vector<world_element> &getMTop() const;

    private:

        //top
        t3v::object2d m_top_hurdle;
        t3v::sprite *m_top_hurdle_sprite=NULL;
        std::vector<world_element> m_top;

    public:
        world();
        ~world();

        void render(float t_delta);
    };

	class player
	{
	private:
		t3v::object2d  m_player_object;
		t3v::sprite *m_player_sprite_small=NULL;
        t3v::sprite *m_player_sprite_big=NULL;

		//position
		float xPos=0;
		float yPos=0;

		//speed
		float xVel=0;
		float yVel=0;

		//misc
		float hp=100;
		bool isSmall;

    public:
		player(const char *path_to_player_sprite_small, const char *path_to_player_sprite_big);
		~player();

		void input();
		void gravity(float t_delta);
		void render(){m_player_object.render();};
        float getHp() const;
        void damage(float hp);
        bool takesDamage(ppf::world &pWorld) const;
        bool takesDamageBig(ppf::world &pWorld) const;
        bool takesDamageSmall(ppf::world &pWorld) const;
        void toggleSize();
        bool getSmall(){return isSmall;};
    };

	class background
	{
	private:
		struct bubble_struct
		{
			t3v::object2d object;
			float xPos;
			float yPos;
			float xVel=0;
			float yVel=0;
		};

		t3v::object2d m_background;
		t3v::sprite *m_background_sprite=NULL;

		t3v::object2d m_bubble;
		t3v::sprite *m_bubble_sprite=NULL;

		std::vector<bubble_struct> bubbles;

	public:
		background();
		~background();

		void render(float t_delta);
	};

	//collision
	bool is_colliding(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
}
