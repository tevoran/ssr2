#include "ssr2.hpp"

ssr::renderer::renderer(const int resx_in, const int resy_in)
{
	resx=resx_in;
	resy=resy_in;
	std::cout << "Using resolution: " << resx << "x" << resy << std::endl;

	//initializing SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window=SDL_CreateWindow("Simple Software Renderer 2 - by T3V", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resx, resy, 0);
	if(window==NULL)
	{
		std::cout << "[ERROR] SDL couldn't create a window" << std::endl;
		exit(0);
	}

	window_surface=SDL_GetWindowSurface(window);
	if(window_surface==NULL)
	{
		std::cout << "[ERROR] window is invalid" << std::endl;
		exit(0);
	}

}

ssr::renderer::~renderer()
{
	SDL_Quit();
}

void ssr::renderer::update()
{
	SDL_UpdateWindowSurface(window);
}