#include "../../includes/miniRT.h"

void	free_canvas(t_canvas *canvas)
{
    int	i;
    int j;

    i = 0;
    while (i < canvas->height)
    {
        j = 0;
        while (j < canvas->width)
        {
            free(canvas->pixels[i][j]);
            j++;
        }
        free(canvas->pixels[i]);
        i++;
    }
    free(canvas->pixels);
    free(canvas);
}

static void	fill_black_canvas(t_canvas *canvas)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			canvas->pixels[i][j] = new_rgb(0, 0, 0);
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
			free_canvas(canvas);
			return (NULL);
		}
		i++;
	}
	fill_black_canvas(canvas);
	return (canvas);
}

t_rgb	*pixel_at(t_canvas *canvas, int x, int y)
{
    return (canvas->pixels[y][x]);
}

void write_pixel(t_canvas *canvas, int x, int y, t_rgb *color)
{
    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
        return ;
    if (canvas->pixels[y][x])
        free(canvas->pixels[y][x]);
    canvas->pixels[y][x] = color;
}
