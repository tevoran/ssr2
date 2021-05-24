#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <cstdio>


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

	private:
		void draw_pixel(const int x, const int y, const ssr::vertex& vertex);

	public:
		renderer(const int resx_in, const int resy_in);
		~renderer();

		void render(ssr::vertex vertex);
		void update();
	};
}

