#include "game.hpp"

ppf::menu::menu()
{

}

ppf::menu::~menu()
{

}

void ppf::menu::run(ppf::background& background, ppf::time& time, t3v::font& font)
{
	t3v::engine& te=t3v::engine::get();

	t3v::object2d fish_big;
	t3v::sprite fish_big_sprite("../assets/Kugelfisch.png");
	fish_big.use_sprite(fish_big_sprite);
	fish_big.scale(4);
	fish_big.position(900,300);

	t3v::object2d fish_small;
	t3v::sprite fish_small_sprite("../assets/Flachfisch.png");
	fish_small.use_sprite(fish_small_sprite);
	fish_small.scale(3);
	fish_small.position(700,325); 


	bool quit=false;
	while(!quit)
	{
		//updates
		te.update();
		time.update();
		te.update_input();
		tmp += time.get_delta();
		//end game in a hacky way, because this basically carries over into the main game loop
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
		}

		//start the actual game
		if(te.key_is_pressed(SDL_SCANCODE_RETURN))
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

		//text
		//game title
	    te.print_single_frame("Puff Puff", font,
                              {0,255,255,255},108,400,50);
		//controls
	    te.print_single_frame("Controls", font,
                              {0,255,255,255},48,100,200);
	    te.print_single_frame("SPACE for jump", font,
                              {0,255,255,255},32,100,300);
	    te.print_single_frame("Q for changing size", font,
                              {0,255,255,255},32,100,400);
	    te.print_single_frame("ENTER for starting the game", font,
                              {0,255,255,255},32,100,500);
	    te.print_single_frame("ESCAPE for ending the game", font,
                              {0,255,255,255},32,100,600);

	    //description
	    te.print_single_frame("You play as this cute puffer fish", font,
                              {0,255,255,255},32,700,250);
	 	fish_big.render();
	 	fish_small.render();
	    te.print_single_frame("It is possible to change your size", font,
                              {0,255,255,255},32,700,450);
	    te.print_single_frame("After a 5 sec cooldown and", font,
                              {0,255,255,255},32,700,525);
	    te.print_single_frame("You will get more points while puffed up", font,
                              {0,255,255,255},32,700,600);
	}
}