#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int parse_ambient(char *line, t_world *world)
{
	char *token;
	char *line_copy = strdup(line);

	// Skip "A "
	token = strtok(line_copy, " ");
	
	// Parse ratio
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	world->ambient.ratio = parse_float(token);

	// Parse RGB
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	world->ambient.color = parse_rgb(token);
	// Normalize color from 0-255 to 0-1
	world->ambient.color.r /= 255.0;
	world->ambient.color.g /= 255.0;
	world->ambient.color.b /= 255.0;

	free(line_copy);
	return (1);
}

int parse_camera(char *line, t_camera *camera)
{
	char tokens[4][50]; // Array to store tokens
	int token_count = 0;
	char *line_copy = strdup(line);
	char *token;
	t_tuple position, orientation;
	float fov;

	// Parse all tokens first
	token = strtok(line_copy, " ");
	while (token && token_count < 4)
	{
		strcpy(tokens[token_count], token);
		token_count++;
		token = strtok(NULL, " ");
	}

	free(line_copy);

	if (token_count < 4)
	{
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

	return (1);
}

int parse_light(char *line, t_world *world)
{
	char tokens[4][50]; // Array to store tokens
	int token_count = 0;
	char *line_copy = strdup(line);
	char *token;
	t_tuple position;
	float brightness;
	t_rgb color;

	// Parse all tokens first
	token = strtok(line_copy, " ");
	while (token && token_count < 4)
	{
		strcpy(tokens[token_count], token);
		token_count++;
		token = strtok(NULL, " ");
	}

	free(line_copy);

	if (token_count < 4)
	{
		return (0);
	}

	// Parse position
	position = parse_tuple(tokens[1], 1); // is_point = 1

	// Parse brightness
	brightness = parse_float(tokens[2]);

	// Parse RGB
	color = parse_rgb(tokens[3]);
	// Normalize color from 0-255 to 0-1 and apply brightness
	color.r = (color.r / 255.0) * brightness;
	color.g = (color.g / 255.0) * brightness;
	color.b = (color.b / 255.0) * brightness;

	t_point_light light = new_point_light(position, color);
	add_light_to_world(world, light);

	return (1);
}

int parse_sphere(char *line, t_world *world)
{
	char tokens[4][50]; // Array to store tokens
	int token_count = 0;
	char *line_copy = strdup(line);
	char *token;
	t_tuple center;
	float radius;
	t_rgb color;

	// Parse all tokens first
	token = strtok(line_copy, " ");
	while (token && token_count < 4)
	{
		strcpy(tokens[token_count], token);
		token_count++;
		token = strtok(NULL, " ");
	}

	free(line_copy);

	if (token_count < 4)
	{
		return (0);
	}

	// Parse center
	center = parse_tuple(tokens[1], 1); // is_point = 1

	// Parse radius
	radius = parse_float(tokens[2]);

	// Parse RGB
	color = parse_rgb(tokens[3]);

	// Create sphere at origin with unit radius
	t_sphere *sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
		
	*sphere = new_sphere(point(0, 0, 0), 1.0);
	
	// Apply transformations: first scale, then translate
	t_matrix scale_matrix = scaling_matrix(radius, radius, radius);
	t_matrix translate_matrix = translation_matrix(center.x, center.y, center.z);
	
	// Combine transformations (translation * scaling)
	sphere->transform = matrix_multiply_by_matrix(translate_matrix, scale_matrix);
	
	// Set material color (normalize RGB values from 0-255 to 0-1)
	sphere->material.color = new_rgb(color.r / 255.0, color.g / 255.0, color.b / 255.0);

	// Clean up matrices
	free_matrix(scale_matrix);
	free_matrix(translate_matrix);

	// Create object and add to world
	t_object obj = new_object(SPHERE, sphere);
	add_object_to_world(world, obj);

	return (1);
}
