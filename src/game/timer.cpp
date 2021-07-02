#include "game/game.hpp"

ppf::time::time()
{
	t_old=std::chrono::steady_clock::now();
}

float ppf::time::get_delta()
{
	return t_delta_float;
}

void ppf::time::update()
{
	t_new=std::chrono::steady_clock::now();
	std::chrono::duration<float> t_delta = std::chrono::duration_cast<std::chrono::duration<float>>(t_new-t_old);
	t_old=t_new;
	t_delta_float=t_delta.count();
}