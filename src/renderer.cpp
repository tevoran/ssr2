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
	memset((void*)window_surface->pixels, 0, resx*resy*sizeof(uint32_t)); //clearing screen
}

void ssr::renderer::draw_pixel(const int x, const int y, const ssr::vertex& vertex)
{ 
	uint32_t *pixel_ptr=(uint32_t*)window_surface->pixels;
	pixel_ptr=pixel_ptr+x+y*resx;

	register uint32_t pixel_color=vertex.r;
	pixel_color=pixel_color<<8;
	pixel_color+=vertex.g;
	pixel_color=pixel_color<<8;
	pixel_color+=vertex.b;

	*pixel_ptr=pixel_color;
}


void ssr::renderer::render(ssr::vertex vertex)
{
	//convertion to screen space 
	//screen space ranges from 0 to 1
	int vertex_screen_x=vertex.x*resx+0.5;
	int vertex_screen_y=vertex.y*resy+0.5;

	draw_pixel(vertex_screen_x, vertex_screen_y, vertex);
}