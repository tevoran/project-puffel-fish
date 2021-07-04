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

	bool quit=false;
	while(!quit)
	{
		//updates
		te.update();
		time.update();
		te.update_input();
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

		//background
		background.render(time.get_delta());

		//text
	    te.print_single_frame("Puff Puff", font,
                              {0,255,255,255},108,400,100);
	}
}