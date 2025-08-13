#include "../../includes/miniRT.h"

void	free_canvas(t_canvas *canvas)
{
    int	i;

    i = 0;
    while (i < canvas->height)
    {
        free(canvas->pixels[i]);
        i++;
    }
    free(canvas->pixels);
    free(canvas);
}

void	fill_black_canvas(t_canvas *canvas)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			canvas->pixels[i][j].r = 0;
			canvas->pixels[i][j].g = 0;
			canvas->pixels[i][j].b = 0;
			j++;
		}
		i++;
	}
}

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*canvas;
	int			i;

	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		return (NULL);
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = malloc(sizeof(t_rgb *) * height);
	if (!canvas->pixels)
	{
		free(canvas);
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		canvas->pixels[i] = malloc(sizeof(t_rgb) * width);
		if (!canvas->pixels[i])
		{
			while (--i >= 0)
				free(canvas->pixels[i]);
			free(canvas->pixels);
			free(canvas);
			return (NULL);
		}
		i++;
	}
	fill_black_canvas(canvas);
	return (canvas);
}

t_rgb	*pixel_at(t_canvas *canvas, int x, int y)
{
    return (&canvas->pixels[y][x]);
}

void write_pixel(t_canvas *canvas, int x, int y, t_rgb color)
{
	canvas->pixels[y][x] = color;
}
