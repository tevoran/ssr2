#include "ssr2.hpp"

ssr::barycentric_interpolation::barycentric_interpolation(
	const int x1_in,
	const int y1_in,
	const int x2_in,
	const int y2_in,
	const int x3_in,
	const int y3_in)
{
	x1=x1_in;
	x2=x2_in;
	x3=x3_in;
	y1=y1_in;
	y2=y2_in;
	y3=y3_in;
	div=(x2-x1)*(y3-y2)-(y2-y1)*(x3-x2);
}

void ssr::barycentric_interpolation::interpolate_pixel(const int x_current, const int y_current, float *a_out, float *b_out, float *c_out)
{
	*a_out=(float)((x2-x_current)*(y3-y_current)-(x3-x_current)*(y2-y_current))
			/div;

	*b_out=(float)((x3-x_current)*(y1-y_current)-(x1-x_current)*(y3-y_current))
			/div;

	*c_out=1-*a_out-*b_out;
}

//barycentric interpolation
void ssr::interpolate(
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
							float *c_out)
{
	int div=(x2-x1)*(y3-y2)-(y2-y1)*(x3-x2);

	*a_out=(float)((x2-x_current)*(y3-y_current)-(x3-x_current)*(y2-y_current))
			/(float)div;

	*b_out=(float)((x3-x_current)*(y1-y_current)-(x1-x_current)*(y3-y_current))
			/(float)div;

	*c_out=1-*a_out-*b_out;
}