#include "includes/miniRT.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_parsed_scene *scene;
	t_canvas *canvas;
	
	if (argc != 2)
	{
		printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}

	// Parse the .rt file directly into world + camera
	scene = parse_rt_file(argv[1]);
	
	if (!scene)
	{
		printf("Failed to parse file\n");
		return (1);
	}

	print_parsed_scene_debug(scene);

	printf("\nSuccessfully loaded scene!\n");
	printf("World contains:\n");
	printf("  - %d objects\n", scene->world->objects->count);
	printf("  - %d lights\n", scene->world->lights->count);
	printf("  - Ambient: ratio=%.2f, color=(%.2f,%.2f,%.2f)\n",
		scene->world->ambient.ratio,
		scene->world->ambient.color.r, scene->world->ambient.color.g, scene->world->ambient.color.b);

	// Render the scene
	printf("\nStarting render...\n");
	canvas = render(scene->camera, scene->world);
	
	if (!canvas)
	{
		printf("Failed to render scene\n");
		free_parsed_scene(scene);
		return (1);
	}

	printf("Render completed! Opening MLX window...\n");
	
	// Display the rendered image using MLX
	open_mlx_screen(canvas);
	
	// Cleanup
	free_parsed_scene(scene);
	
	return (0);
}
