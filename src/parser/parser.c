#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"
#include <string.h>

t_scene *parse_rt_file(const char *filename)
{
	int fd;
	char *line;
	t_scene *scene;
	int sphere_capacity = 10;
	int light_capacity = 10;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (NULL);
	}

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);

	// Initialize scene
	scene->sphere_count = 0;
	scene->light_count = 0;
	scene->spheres = malloc(sizeof(t_sphere) * sphere_capacity);
	scene->lights = malloc(sizeof(t_point_light) * light_capacity);
	
	if (!scene->spheres || !scene->lights)
	{
		free(scene->spheres);
		free(scene->lights);
		free(scene);
		close(fd);
		return (NULL);
	}

	// Parse file line by line
	while ((line = get_next_line(fd)) != NULL)
	{
		// Skip empty lines and comments
		if (line[0] == '\n' || line[0] == '#' || line[0] == '\0')
		{
			free(line);
			continue;
		}

		// Remove newline if present
		int len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		// Parse based on identifier
		if (line[0] == 'A' && line[1] == ' ')
		{
			if (!parse_ambient(line, &scene->ambient))
			{
				printf("Error parsing ambient line: %s\n", line);
			}
		}
		else if (line[0] == 'C' && line[1] == ' ')
		{
			if (!parse_camera(line, &scene->camera))
			{
				printf("Error parsing camera line: %s\n", line);
			}
		}
		else if (line[0] == 'L' && line[1] == ' ')
		{
			if (scene->light_count >= light_capacity)
			{
				light_capacity *= 2;
				scene->lights = realloc(scene->lights, sizeof(t_point_light) * light_capacity);
			}
			if (!parse_light(line, &scene->lights[scene->light_count]))
			{
				printf("Error parsing light line: %s\n", line);
			}
			else
			{
				scene->light_count++;
			}
		}
		else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		{
			if (scene->sphere_count >= sphere_capacity)
			{
				sphere_capacity *= 2;
				scene->spheres = realloc(scene->spheres, sizeof(t_sphere) * sphere_capacity);
			}
			if (!parse_sphere(line, &scene->spheres[scene->sphere_count]))
			{
				printf("Error parsing sphere line: %s\n", line);
			}
			else
			{
				scene->sphere_count++;
			}
		}

		free(line);
	}

	close(fd);
	return (scene);
}

void free_scene(t_scene *scene)
{
	if (!scene)
		return;
	
	if (scene->spheres)
		free(scene->spheres);
	if (scene->lights)
		free(scene->lights);
	free(scene);
}

void print_scene_debug(t_scene *scene)
{
	int i;

	if (!scene)
	{
		printf("Scene is NULL\n");
		return;
	}

	printf("=== SCENE DEBUG INFO ===\n");
	
	// Print ambient
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", scene->ambient.ratio);
	printf("  Color: (%.2f, %.2f, %.2f)\n", 
		scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);

	// Print camera
	printf("Camera:\n");
	printf("  Size: %dx%d\n", scene->camera.hsize, scene->camera.vsize);
	printf("  FOV: %.2f degrees\n", scene->camera.field_of_view);
	printf("  Pixel Size: %.6f\n", scene->camera.pixel_size);

	// Print lights
	printf("Lights (%d):\n", scene->light_count);
	for (i = 0; i < scene->light_count; i++)
	{
		printf("  Light %d:\n", i + 1);
		printf("    Position: (%.2f, %.2f, %.2f)\n",
			scene->lights[i].position.x, scene->lights[i].position.y, scene->lights[i].position.z);
		printf("    Intensity: (%.2f, %.2f, %.2f)\n",
			scene->lights[i].intensity.r, scene->lights[i].intensity.g, scene->lights[i].intensity.b);
	}

	// Print spheres
	printf("Spheres (%d):\n", scene->sphere_count);
	for (i = 0; i < scene->sphere_count; i++)
	{
		printf("  Sphere %d:\n", i + 1);
		printf("    Center: (%.2f, %.2f, %.2f)\n",
			scene->spheres[i].center.x, scene->spheres[i].center.y, scene->spheres[i].center.z);
		printf("    Radius: %.2f\n", scene->spheres[i].radius);
		printf("    Color: (%.2f, %.2f, %.2f)\n",
			scene->spheres[i].material.color.r, scene->spheres[i].material.color.g, scene->spheres[i].material.color.b);
	}
	
	printf("========================\n");
}
