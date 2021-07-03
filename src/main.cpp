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
	float time_passed;

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");

	te.activate_fps_counter(true, &font);


	//player
	ppf::player player("../assets/Kugelfisch.png");

	//background
	ppf::background background;

	//world
	ppf::world world;


	bool quit=false;
	while(!quit)
	{
		//updates
		te.update();
		time.update();
		te.update_input();
		time_passed += time.get_delta();
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
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
	    //test for damage function TODO: delete before release
	    if((int) time_passed % 5 == 0)
	        //player.damage(0.05);


	    //misc
        te.print_single_frame("Time: "+ std::to_string((int) time_passed) + " seconds", font,
                              {0,255,255,255}, 36, 525, 25);
        if(player.getHp() < 0)
            quit=true;
	}

	return 0;
}