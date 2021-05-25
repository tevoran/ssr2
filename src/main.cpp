#include "ssr2.hpp"

#define REPETITIONS 10

int main()
{
	//test triangle
	ssr::vertex vertex[3];
	vertex[0].x=0.1;
	vertex[0].y=0.1;
	vertex[0].z=0;
	vertex[0].r=250;
	vertex[0].g=0;
	vertex[0].b=0;

	vertex[1].x=0.8;
	vertex[1].y=0.3;
	vertex[1].z=0;
	vertex[1].r=0;
	vertex[1].g=250;
	vertex[1].b=0;

	vertex[2].x=0.3;
	vertex[2].y=0.8;
	vertex[2].z=0;
	vertex[2].r=0;
	vertex[2].g=0;
	vertex[2].b=250;

	ssr::renderer renderer(1920,1080);
	
	using namespace std::chrono;
	steady_clock::time_point t_begin=steady_clock::now();

	//main loop
	for(int i=0; i<REPETITIONS; i++)
	{
		renderer.render(vertex[0], vertex[1], vertex[2]);
		renderer.update();
	}

	steady_clock::time_point t_end=steady_clock::now();
	duration<float> t_delta=duration_cast<duration<float>>(t_end-t_begin);
	std::cout << "rendering took: " << t_delta.count() << "s" << std::endl;
	std::cout << "in " << REPETITIONS << " repetitions" << std::endl;
	std::cout << "1 frame took: " << (t_delta.count()*1000)/REPETITIONS << " ms on average" << std::endl;

	return 0;
}