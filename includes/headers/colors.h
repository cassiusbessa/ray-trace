#ifndef COLORS_H
# define COLORS_H

# include "types.h"

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

// Color creation and operations
t_rgb	new_rgb(float r, float g, float b);
t_rgb	add_rgb(t_rgb c1, t_rgb c2);
t_rgb	sub_rgb(t_rgb c1, t_rgb c2);
t_rgb	multiply_rgb_by_scalar(t_rgb c, float scalar);
t_rgb	multiply_rgb_by_rgb(t_rgb c1, t_rgb c2);
int		equal_rgb(t_rgb c1, t_rgb c2);
void	print_rgb(t_rgb c);
t_rgb	clamp_color(t_rgb c);

#endif
