#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"
#include <string.h>

int parse_ambient(char *line, t_ambient *ambient)
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
	ambient->ratio = parse_float(token);

	// Parse RGB
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	ambient->color = parse_rgb(token);
	// Normalize color from 0-255 to 0-1
	ambient->color.r /= 255.0;
	ambient->color.g /= 255.0;
	ambient->color.b /= 255.0;

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
	camera->transform = view_transform(position, add_tuples(position, orientation), up);

	return (1);
}

int parse_sphere(char *line, t_sphere *sphere)
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

	// Create sphere
	*sphere = new_sphere(center, radius);
	
	// Set material color (normalize RGB values from 0-255 to 0-1)
	sphere->material.color = new_rgb(color.r / 255.0, color.g / 255.0, color.b / 255.0);

	return (1);
}

#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"
#include <string.h>

int parse_ambient(char *line, t_ambient *ambient)
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
	ambient->ratio = parse_float(token);

	// Parse RGB
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	ambient->color = parse_rgb(token);
	// Normalize color from 0-255 to 0-1
	ambient->color.r /= 255.0;
	ambient->color.g /= 255.0;
	ambient->color.b /= 255.0;

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
	camera->transform = view_transform(position, add_tuples(position, orientation), up);

	return (1);
}

int parse_light(char *line, t_point_light *light)
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

	*light = new_point_light(position, color);

	return (1);
}

int parse_sphere(char *line, t_sphere *sphere)
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

	// Create sphere
	*sphere = new_sphere(center, radius);
	
	// Set material color (normalize RGB values from 0-255 to 0-1)
	sphere->material.color = new_rgb(color.r / 255.0, color.g / 255.0, color.b / 255.0);

	return (1);
}

int parse_sphere(char *line, t_sphere *sphere)
{
	char *token;
	char *line_copy = strdup(line);
	t_tuple center;
	float radius;
	t_rgb color;

	// Skip "sp "
	token = strtok(line_copy, " ");
	
	// Parse center
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	center = parse_tuple(token, 1); // is_point = 1

	// Parse radius
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	radius = parse_float(token);

	// Parse RGB
	token = strtok(NULL, " ");
	if (!token)
	{
		free(line_copy);
		return (0);
	}
	color = parse_rgb(token);

	// Create sphere
	*sphere = new_sphere(center, radius);
	
	// Set material color (normalize RGB values from 0-255 to 0-1)
	sphere->material.color = new_rgb(color.r / 255.0, color.g / 255.0, color.b / 255.0);

	free(line_copy);
	return (1);
}
