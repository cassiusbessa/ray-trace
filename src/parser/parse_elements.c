#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int parse_ambient(char *line, t_world *world)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2])
	{
		if (tokens)
		{
			for (i = 0; tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
		}
		return (0);
	}

	// Parse ratio
	world->ambient.ratio = parse_float(tokens[1]);

	// Parse RGB (already normalized by parse_rgb)
	world->ambient.color = parse_rgb(tokens[2]);

	// Free tokens
	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);
	
	return (1);
}

int parse_camera(char *line, t_camera *camera)
{
	char **tokens;
	int i;
	t_tuple position, orientation;
	float fov;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
	{
		if (tokens)
		{
			for (i = 0; tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
		}
		return (0);
	}

	// Parse position
	position = parse_tuple(tokens[1], 1); // is_point = 1

	// Parse orientation (normalized direction vector)
	orientation = parse_tuple(tokens[2], 0); // is_point = 0

	// Parse FOV
	fov = parse_float(tokens[3]);

	// Create camera with default dimensions
	*camera = new_camera(WIDTH, HEIGHT, fov * M_PI / 180.0); // Convert degrees to radians
	
	// Set camera transform using view_transform
	t_tuple up = vector(0, 1, 0); // Default up vector
	orientation = normalize_vector(orientation); // Normalize the direction vector
	t_tuple target = add_tuples(position, orientation);
	
	// Debug camera setup
	printf("DEBUG Camera Setup:\n");
	printf("  Position: (%.2f, %.2f, %.2f)\n", position.x, position.y, position.z);
	printf("  Direction: (%.2f, %.2f, %.2f)\n", orientation.x, orientation.y, orientation.z);
	printf("  Target: (%.2f, %.2f, %.2f)\n", target.x, target.y, target.z);
	
	camera->transform = view_transform(position, target, up);

	// Free tokens
	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);

	return (1);
}

int parse_light(char *line, t_world *world)
{
	char **tokens;
	int i;
	t_tuple position;
	float brightness;
	t_rgb color;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
	{
		if (tokens)
		{
			for (i = 0; tokens[i]; i++)
				free(tokens[i]);
			free(tokens);
		}
		return (0);
	}

	// Parse position
	position = parse_tuple(tokens[1], 1); // is_point = 1

	// Parse brightness
	brightness = parse_float(tokens[2]);

	// Parse RGB (already normalized by parse_rgb)
	color = parse_rgb(tokens[3]);
	// Apply brightness
	color.r = color.r * brightness;
	color.g = color.g * brightness;
	color.b = color.b * brightness;

	t_point_light light = new_point_light(position, color);
	add_light_to_world(world, light);

	// Free tokens
	for (i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);

	return (1);
}

int parse_sphere(char *line, t_world *world)
{
	char **tokens;
	t_tuple center;
	float radius;
	t_rgb color;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
		return (destroy_2d((void**)tokens), 0);
	
	center = parse_tuple(tokens[1], 1);
	radius = parse_float(tokens[2]);
	color = parse_rgb(tokens[3]);
	
	t_sphere *sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return(destroy_2d((void**)tokens), 0);		
	
	*sphere = new_sphere(point(0, 0, 0), 1.0);
	t_object obj = new_object(SPHERE, sphere);
	obj.material.color = color;
	set_object_transform(&obj, scaling_matrix(radius, radius, radius));
	set_object_transform(&obj, translation_matrix(center.x, center.y, center.z));
	
	add_object_to_world(world, obj);
	destroy_2d((void**)tokens);
	return (1);
}
