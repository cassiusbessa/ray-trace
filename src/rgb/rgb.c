#include "../../includes/miniRT.h"

t_rgb	new_rgb(float r, float g, float b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_rgb	add_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	result = new_rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	return (result);
}

t_rgb	sub_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	result = new_rgb(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
	return (result);
}

t_rgb	multiply_rgb_by_scalar(t_rgb c, float scalar)
{
	t_rgb	result;

	result = new_rgb(c.r * scalar, c.g * scalar, c.b * scalar);
	return (result);
}

t_rgb	multiply_rgb_by_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	result = new_rgb(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
	return (result);
}
