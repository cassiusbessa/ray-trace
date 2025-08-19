#include "../../includes/miniRT.h"

int equal_rgb(t_rgb c1, t_rgb c2)
{
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}


t_rgb clamp_color(t_rgb c)
{
	c.r = fmin(fmax(c.r, 0), 1);
	c.g = fmin(fmax(c.g, 0), 1);
	c.b = fmin(fmax(c.b, 0), 1);
	return c;
}