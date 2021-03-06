#include "te.hpp"
#include "game/game.hpp"



int main()
{
	t3v::engine& te=t3v::engine::get();

	//setting properties
	te.set_resx(1366);
	te.set_resy(768);
	te.set_fullscreen(false);
	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER_SINGLE_THREAD);

	//timer
	srand(time(NULL));
	ppf::time time;
	float time_passed = 0;
	float size_cd = 0; //cooldown counter for size toggle
	float tmp = 0.5;

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");
	bool activeFPS = false;
	te.activate_fps_counter(activeFPS, &font);


	//player
	ppf::player player("../assets/Flachfisch.png", "../assets/Kugelfisch.png");
	float points=0;

	//menu
	ppf::menu menu;

	//background
	ppf::background background;

	//world
	ppf::world world;


	menu.run(background, time, font);

	bool quit=false;
	while(!quit)
	{
		//updates 
		te.update(); 
		time.update();
		te.update_input();
		time_passed += time.get_delta();
		size_cd += time.get_delta();
		tmp += time.get_delta();
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
		}

        if(te.key_is_pressed(SDL_SCANCODE_F) && tmp > 0.5){
            activeFPS = !activeFPS;
            te.activate_fps_counter(activeFPS, &font);
            tmp = 0;
        }

		//background
		background.render(time.get_delta());

		//world
		world.render(time.get_delta());

		//player
		player.input();
	    player.gravity(time.get_delta());
	    player.render();
	    te.print_single_frame("HP: " + std::to_string((int)player.getHp()), font,
                              {255,0,0,255},48,1100,25);
	    //test for collisions doing damage
	    if(player.takesDamage(world))
	        player.damage(PLAYER_DAMAGE_SPEED*time.get_delta());


	    //misc
        te.print_single_frame("Points: "+ std::to_string((int) points), font,
                              {0,255,255,255}, 36, 525, 25);

        if(player.getSmall())
        {
        	points+=PLAYER_POINTS_SMALL_SPEED*time.get_delta();
        }
        else
        {
        	points+=PLAYER_POINTS_BIG_SPEED*time.get_delta();        	
        }

        if(te.key_is_pressed(SDL_SCANCODE_Q) && size_cd > 5){
            player.toggleSize();
            size_cd = 0;
        }

        if(player.getHp() < 0) {
            while (!quit) {
                te.update();
                te.update_input();
                if (te.key_is_pressed(SDL_SCANCODE_ESCAPE)) {
                    quit = true;
                }

                background.render(time.get_delta());
                te.print_single_frame("Thanks for Playing!", font, {0, 255, 255, 255},
                                      36, 350, 200);
                te.print_single_frame("You got " + std::to_string((int) points) + " points", font,
                                      {0, 255, 255, 255}, 36, 525, 400);

                te.print_single_frame("Press ENTER to restart", font,
                                      {0, 255, 255, 255}, 64, 325, 600);

                //restart
                if(te.key_is_pressed(SDL_SCANCODE_RETURN))
                {
                	player.resetHP();
                	player.resetPos();
                	size_cd=0;
                	time_passed = 0;
                	points=0;
                	break;
                }

            }
        }
	}

	return 0;
}