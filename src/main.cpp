#include "ssr2.hpp"

int main()
{
	//test vertex
	ssr::vertex vertex;
	vertex.x=0;
	vertex.y=0;
	vertex.z=0;
	vertex.r=255;
	vertex.g=255;
	vertex.b=255;

	ssr::renderer renderer(800,800);
	
	//main loop
	for(int i=0; i<10; i++)
	{
		renderer.update();
		SDL_Delay(300);
	}
	return 0;
}