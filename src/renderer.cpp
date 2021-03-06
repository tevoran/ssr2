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

	num_cpu=std::thread::hardware_concurrency();
	std::cout << "Usable CPU cores or threads: " << num_cpu << std::endl;
}

ssr::renderer::~renderer()
{
	SDL_Quit();
}

void ssr::renderer::update()
{
	SDL_UpdateWindowSurface(window);
	memset(window_surface->pixels, 0, resx*resy*sizeof(uint32_t)); //clearing screen
}


void ssr::renderer::rasterize_triangle(const int y_begin, const int y_end, ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3)
{
	//convertion to screen space 
	//screen space ranges from 0 to 1
	int screen1_x=vertex1.x*resx+0.5;
	int screen1_y=vertex1.y*resy+0.5;

	int screen2_x=vertex2.x*resx+0.5;
	int screen2_y=vertex2.y*resy+0.5;

	int screen3_x=vertex3.x*resx+0.5;
	int screen3_y=vertex3.y*resy+0.5;


	//calculating the side along the y-axis of the triangle
	if(screen3_y-screen1_y==0)
	{
		screen3_y++;
	}
	float current_x, delta;
	delta=(screen3_x-screen1_x)/(screen3_y-screen1_y);

	//creating bounding box for rasterizing
	int x_start=screen1_x;
	if(screen2_x<x_start)
	{
		x_start=screen2_x;
	}
	if(screen3_x<x_start)
	{
		x_start=screen3_x;
	}

	int x_stop=screen1_x;
	if(screen2_x>x_stop)
	{
		x_stop=screen2_x;
	}
	if(screen3_x>x_stop)
	{
		x_stop=screen3_x;
	}

	int y_start=screen1_y;
	if(screen2_y<y_start)
	{
		y_start=screen2_y;
	}
	if(screen3_y<y_start)
	{
		y_start=screen3_y;
	}

	int y_stop=screen1_y;
	if(screen2_y>y_stop)
	{
		y_stop=screen2_y;
	}
	if(screen3_y>y_stop)
	{
		y_stop=screen3_y;
	}

	//making sure to render one part of the image only by one thread
	if(y_start<y_begin)
	{
		y_start=y_begin;
	}

	current_x=(y_start-screen1_y)*delta+screen1_x;

	//if triangle is not in the area that is rendered by the thread then it is dropped
	if(y_start>y_stop)
	{
		return;
	}

	if(y_stop>y_end)
	{
		y_stop=y_end;
	}

	float a=0, b=0, c=0; //barycentric coordinates

	ssr::barycentric_interpolation triangle(
				screen1_x,
				screen1_y,
				screen2_x,
				screen2_y,
				screen3_x,
				screen3_y);

	//rasterizing loop
	for(int iy=y_start; iy<y_stop; iy++)
	{
		current_x+=delta;
		bool last_pixel_drawn=false;
		uint32_t *pixel_ptr=NULL;

		//rendering a line
		for(int ix=(int)current_x; ix<x_stop; ix++)
		{
			triangle.interpolate_pixel(ix,iy,&a,&b,&c);
			
			//condition of a pixel inside the triangle
			if(a<1 && a>0 && b<1 && b>0 && c<1 && c>0) 
			{
				if(last_pixel_drawn==false) //if this is the first pixel of the current line
				{
					//setting up pixel pointer
					pixel_ptr=(uint32_t*)window_surface->pixels;
					pixel_ptr=pixel_ptr+ix+iy*resx;
				}
				last_pixel_drawn=true;
				uint8_t r=(float)(a*(float)vertex1.r)+(float)(b*(float)vertex2.r)+(float)(c*(float)vertex3.r);
				uint8_t g=(float)(a*(float)vertex1.g)+(float)(b*(float)vertex2.g)+(float)(c*(float)vertex3.g);
				uint8_t b=(float)(a*(float)vertex1.b)+(float)(b*(float)vertex2.b)+(float)(c*(float)vertex3.b);
				draw_pixel(pixel_ptr, r,g,b);
				pixel_ptr++;
			}
			//if last pixel of a horizontal line is drawn, go to next line
			else
			{
				if(last_pixel_drawn==true)
				{
					break;
				}
			}
		}
	}

}

void ssr::renderer::render(ssr::vertex& vertex1, ssr::vertex& vertex2, ssr::vertex& vertex3)
{
	//sorting vertices along the y-axis
	if(vertex2.y<vertex1.y)
	{
		std::swap(vertex1, vertex2);
	}
	if(vertex3.y<vertex2.y)
	{
		std::swap(vertex2, vertex3);
	}
	if(vertex2.y<vertex1.y)
	{
		std::swap(vertex1, vertex2);
	}

	int num_threads=0;
	rasterize_triangle(0, resy, vertex1, vertex2, vertex3);
}