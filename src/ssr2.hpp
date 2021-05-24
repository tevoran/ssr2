#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>


namespace ssr
{
	class vertex
	{
	private:
	public:
		float x,y,z; //coordinates
		char r,g,b; //colors
	};

	class renderer
	{
	private:
		int resx;
		int resy;
		SDL_Window *window=NULL;
		SDL_Surface *window_surface=NULL;
	public:
		renderer(const int resx_in, const int resy_in);
		~renderer();

		void update();
	};
}

