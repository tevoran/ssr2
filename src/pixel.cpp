#include "ssr2.hpp"

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

void ssr::renderer::draw_pixel(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b)
{
	uint32_t *pixel_ptr=(uint32_t*)window_surface->pixels;
	pixel_ptr=pixel_ptr+x+y*resx;

	register uint32_t pixel_color=r;
	pixel_color=pixel_color<<8;
	pixel_color+=g;
	pixel_color=pixel_color<<8;
	pixel_color+=b;

	*pixel_ptr=pixel_color;
}

void ssr::renderer::draw_pixel(uint32_t *pixel_ptr, const uint8_t r, const uint8_t g, const uint8_t b)
{
	register uint32_t pixel_color=r;
	pixel_color=pixel_color<<8;
	pixel_color+=g;
	pixel_color=pixel_color<<8;
	pixel_color+=b;

	*pixel_ptr=pixel_color;	
}