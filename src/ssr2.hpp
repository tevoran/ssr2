#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <chrono>
#include <ratio>


namespace ssr
{
	class vertex
	{
	private:
	public:
		float x,y,z; //coordinates
		uint8_t r,g,b; //colors
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
		void draw_pixel(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b);
		void rasterize_triangle(const int y_begin, const int y_end, ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3);

		//barycentric interpolation
		void interpolate(
			const int x1,
			const int y1,
			const int x2,
			const int y2,
			const int x3,
			const int y3,
			const int x_current,
			const int y_current,
			float *a_out,
			float *b_out,
			float *c_out);

	public:
		renderer(const int resx_in, const int resy_in);
		~renderer();

		void render(ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3);
		void update();
	};
}

