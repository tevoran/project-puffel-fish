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

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");

	te.activate_fps_counter(true, &font);


	//player
	ppf::player player("../assets/Kugelfisch.png");


	bool quit=false;
	while(!quit)
	{
		player.render();



		te.update();

		te.update_input();
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
		}
	}

	return 0;
}