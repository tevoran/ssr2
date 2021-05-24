#include "ssr2.hpp"

int main()
{
	//test vertex
	ssr::vertex vertex;
	vertex.x=0.3;
	vertex.y=0.3;
	vertex.z=0;
	vertex.r=250;
	vertex.g=250;
	vertex.b=250;

	ssr::renderer renderer(800,800);
	
	//main loop
	for(int i=0; i<10; i++)
	{
		renderer.render(vertex);
		renderer.update();
		SDL_Delay(300);
	}
	return 0;
}