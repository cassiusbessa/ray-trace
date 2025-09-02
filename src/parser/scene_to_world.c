#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"

t_world *scene_to_world(t_scene *scene)
{
	t_world *world;
	int i;

	if (!scene)
		return (NULL);

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);

	// Create world with ambient from scene
	*world = new_world_with_ambient(scene->ambient);

	// Add lights to world
	for (i = 0; i < scene->light_count; i++)
	{
		add_light_to_world(world, scene->lights[i]);
	}

	// Add spheres to world
	for (i = 0; i < scene->sphere_count; i++)
	{
		t_sphere *sphere_data = malloc(sizeof(t_sphere));
		if (sphere_data)
		{
			*sphere_data = scene->spheres[i];
			t_object sphere_obj = new_object(SPHERE, sphere_data);
			add_object_to_world(world, sphere_obj);
		}
	}

	return (world);
}
