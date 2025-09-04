#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"

t_parsed_scene *parse_rt_file(const char *filename)
{
	int fd;
	char *line;
	t_parsed_scene *scene;

	printf("Parsing file: %s\n", filename);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (NULL);
	}

	// Create parsed scene
	scene = malloc(sizeof(t_parsed_scene));
	if (!scene)
	{
		close(fd);
		return (NULL);
	}
	
	// Create world
	scene->world = malloc(sizeof(t_world));
	if (!scene->world)
	{
		free(scene);
		close(fd);
		return (NULL);
	}
	
	// Initialize world with default ambient
	*(scene->world) = new_world();

	// Parse file line by line using get_next_line
	while ((line = get_next_line(fd)) != NULL)
	{
		// Skip empty lines and comments
		if (line[0] == '\n' || line[0] == '#' || line[0] == '\0')
		{
			free(line);
			continue;
		}

		// Remove newline if present
		int len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		// Parse based on identifier
		if (line[0] == 'A' && line[1] == ' ')
		{
			if (!parse_ambient(line, scene->world))
			{
				printf("Error parsing ambient line: %s\n", line);
				free(line);
				free_parsed_scene(scene);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] == 'C' && line[1] == ' ')
		{
			if (!parse_camera(line, &scene->camera))
			{
				printf("Error parsing camera line: %s\n", line);
				free(line);
				free_parsed_scene(scene);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] == 'L' && line[1] == ' ')
		{
			if (!parse_light(line, scene->world))
			{
				printf("Error parsing light line: %s\n", line);
				free(line);
				free_parsed_scene(scene);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		{
			if (!parse_sphere(line, scene->world))
			{
				printf("Error parsing sphere line: %s\n", line);
				free(line);
				free_parsed_scene(scene);
				close(fd);
				return (NULL);
			}
		}
		else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		{
    		if (!parse_cylinder(line, scene->world))
    		{
        		printf("Error parsing cylinder line: %s\n", line);
        		free(line);
				free_parsed_scene(scene);
				close(fd);
				return (NULL);
    		}
		}
		else
		{
			printf("Error: Unknown element identifier in line: %s\n", line);
			free(line);
			free_parsed_scene(scene);
			close(fd);
			return (NULL);
		}

		free(line);
	}

	close(fd);
	printf("Successfully parsed file!\n");
	return (scene);
}

void free_parsed_scene(t_parsed_scene *scene)
{
	if (!scene)
		return;
	
	if (scene->world)
	{
		free_world(scene->world);
		free(scene->world);
	}
	free(scene);
}

void print_parsed_scene_debug(t_parsed_scene *scene)
{
	if (!scene)
	{
		printf("Parsed scene is NULL\n");
		return;
	}

	printf("=== PARSED SCENE DEBUG INFO ===\n");
	
	// Print ambient
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", scene->world->ambient.ratio);
	printf("  Color: (%.2f, %.2f, %.2f)\n", 
		scene->world->ambient.color.r, scene->world->ambient.color.g, scene->world->ambient.color.b);

	// Print camera
	printf("Camera:\n");
	printf("  Size: %dx%d\n", scene->camera.hsize, scene->camera.vsize);
	printf("  FOV: %.2f degrees\n", scene->camera.field_of_view);
	printf("  Pixel Size: %.6f\n", scene->camera.pixel_size);

	// Print lights
	printf("Lights (%d):\n", scene->world->lights->count);
	t_point_light_node *current_light = scene->world->lights->head;
	int light_index = 1;
	while (current_light)
	{
		printf("  Light %d:\n", light_index);
		printf("    Position: (%.2f, %.2f, %.2f)\n",
			current_light->light.position.x, current_light->light.position.y, current_light->light.position.z);
		printf("    Intensity: (%.2f, %.2f, %.2f)\n",
			current_light->light.intensity.r, current_light->light.intensity.g, current_light->light.intensity.b);
		current_light = current_light->next;
		light_index++;
	}

	// Print objects (spheres)
	printf("Objects (%d):\n", scene->world->objects->count);
	t_object_node *current_obj = scene->world->objects->head;
	int obj_index = 1;
	while (current_obj)
	{
		if (current_obj->object.data && current_obj->object.type == SPHERE)
		{
			t_sphere *sphere = (t_sphere *)current_obj->object.data;
			printf("  Sphere %d:\n", obj_index);
			printf("    Center: (%.2f, %.2f, %.2f)\n",
				sphere->center.x, sphere->center.y, sphere->center.z);
			printf("    Radius: %.2f\n", sphere->radius);
			printf("    Color: (%.2f, %.2f, %.2f)\n",
				current_obj->object.material.color.r, current_obj->object.material.color.g, current_obj->object.material.color.b);
		}
		else if (current_obj->object.type == CYLINDER)
		{
    		t_cylinder *cyl = (t_cylinder *)current_obj->object.data;
    		printf("  Cylinder %d:\n", obj_index);
    		printf("    Radius: %.2f, Height: %.2f\n", cyl->radius, cyl->height);
    		printf("    Color: (%.2f, %.2f, %.2f)\n",
        	current_obj->object.material.color.r,
        	current_obj->object.material.color.g,
        	current_obj->object.material.color.b);
		}
		current_obj = current_obj->next;
		obj_index++;
	}
	
	printf("========================\n");
}
