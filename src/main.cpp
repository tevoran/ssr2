#include "ssr2.hpp"

int main()
{
	//test triangle
	ssr::vertex vertex[3];
	vertex[0].x=0.1;
	vertex[0].y=0.1;
	vertex[0].z=0;
	vertex[0].r=250;
	vertex[0].g=250;
	vertex[0].b=250;

	vertex[1].x=0.8;
	vertex[1].y=0.3;
	vertex[1].z=0;
	vertex[1].r=250;
	vertex[1].g=250;
	vertex[1].b=250;

	vertex[2].x=0.3;
	vertex[2].y=0.8;
	vertex[2].z=0;
	vertex[2].r=250;
	vertex[2].g=250;
	vertex[2].b=250;

	ssr::renderer renderer(800,800);
	
	//main loop
	for(int i=0; i<10; i++)
	{
		renderer.render(vertex[0], vertex[1], vertex[2]);
		renderer.update();
		SDL_Delay(300);
	}
	return 0;
}