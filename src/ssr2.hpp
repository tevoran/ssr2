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
	
	class barycentric_interpolation
	{
	private:
		float div=0;
		int x1=0;
		int y1=0;
		int x2=0;
		int y2=0;
		int x3=0;
		int y3=0;
	public:
		barycentric_interpolation(
			const int x1_in,
			const int y1_in,
			const int x2_in,
			const int y2_in,
			const int x3_in,
			const int y3_in);
		void interpolate_pixel(const int x_current, const int y_current, float *a_out, float *b_out, float *c_out);
	};


	struct vertex
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
		void draw_pixel(uint32_t *pixel_ptr, const uint8_t r, const uint8_t g, const uint8_t b);
		void draw_pixel(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b);
		void rasterize_triangle(const int y_begin, const int y_end, ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3);

	public:
		renderer(const int resx_in, const int resy_in);
		~renderer();

		void render(ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3);
		void update();
	};
}

