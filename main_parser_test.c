#include "includes/miniRT.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_scene *scene;
	
	if (argc != 2)
	{
		printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}

	printf("Parsing file: %s\n", argv[1]);
	scene = parse_rt_file(argv[1]);
	
	if (!scene)
	{
		printf("Failed to parse file\n");
		return (1);
	}

	printf("Successfully parsed file!\n");
	print_scene_debug(scene);

	// Test scene to world conversion
	t_world *world = scene_to_world(scene);
	if (world)
	{
		printf("\nSuccessfully converted scene to world!\n");
		printf("World contains:\n");
		printf("  - %d objects\n", world->objects->count);
		printf("  - %d lights\n", world->lights->count);
		printf("  - Ambient: ratio=%.2f, color=(%.2f,%.2f,%.2f)\n",
			world->ambient.ratio,
			world->ambient.color.r, world->ambient.color.g, world->ambient.color.b);
		
		free_world(world);
		free(world);
	}
	else
	{
		printf("Failed to convert scene to world\n");
	}

	free_scene(scene);
	return (0);
}
