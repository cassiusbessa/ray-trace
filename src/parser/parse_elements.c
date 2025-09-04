#include "../../includes/miniRT.h"


int parse_ambient(char *line, t_world *world)
{
	char **tokens;
	float ratio;
	t_rgb color;

	tokens = ft_split(line, ' ');
	
	// Validate parameter count (A ratio color)
	if (!validate_parameter_count(tokens, "Ambient light", 3))
	{
		destroy_2d((void**)tokens);
		return (0);
	}

	// Parse and validate ratio (must be between 0.0 and 1.0)
	ratio = parse_float(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
	{
		printf("Error: Ambient light ratio must be between 0.0 and 1.0, got %.2f\n", ratio);
		destroy_2d((void**)tokens);
		return (0);
	}
	world->ambient.ratio = ratio;

	// Parse and validate RGB
	if (!validate_and_parse_rgb(tokens[2], &color))
	{
		printf("Error: Invalid RGB values in ambient light: '%s'\n", tokens[2]);
		destroy_2d((void**)tokens);
		return (0);
	}
	world->ambient.color = color;

	// Free tokens
	destroy_2d((void**)tokens);
	
	return (1);
}

int parse_camera(char *line, t_camera *camera)
{
	char **tokens;
	float fov;
	t_tuple position, direction;

	tokens = ft_split(line, ' ');
	
	// Validate parameter count (C position direction fov)
	if (!validate_parameter_count(tokens, "Camera", 4))
	{
		destroy_2d((void**)tokens);
		return (0);
	}

	// Parse position
	position = parse_tuple(tokens[1], 1);
	
	// Parse direction and validate it's normalized
	direction = normalize_vector(parse_tuple(tokens[2], 0));
	
	// Parse and validate FOV (must be between 0 and 180 degrees)
	fov = parse_float(tokens[3]);
	if (fov <= 0 || fov >= 180)
	{
		printf("Error: Camera FOV must be between 0 and 180 degrees, got %.2f\n", fov);
		destroy_2d((void**)tokens);
		return (0);
	}

	*camera = new_camera(WIDTH, HEIGHT, fov * M_PI / 180.0); // Convert degrees to radians
	camera->transform = view_transform(position, add_tuples(position, direction), vector(0, 1, 0));
	
	destroy_2d((void**)tokens);
	return (1);
}

int parse_light(char *line, t_world *world)
{
	char **tokens;
	t_tuple position;
	float brightness;
	t_rgb color;
	t_point_light light;

	tokens = ft_split(line, ' ');
	
	// Validate parameter count (L position brightness color)
	if (!validate_parameter_count(tokens, "Light", 4))
	{
		destroy_2d((void**)tokens);
		return (0);
	}

	// Parse position
	position = parse_tuple(tokens[1], 1);
	
	// Parse and validate brightness (must be between 0.0 and 1.0)
	brightness = parse_float(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		printf("Error: Light brightness must be between 0.0 and 1.0, got %.2f\n", brightness);
		destroy_2d((void**)tokens);
		return (0);
	}

	// Parse and validate RGB
	if (!validate_and_parse_rgb(tokens[3], &color))
	{
		printf("Error: Invalid RGB values in light: '%s'\n", tokens[3]);
		destroy_2d((void**)tokens);
		return (0);
	}

	// Apply brightness to color
	color.r = color.r * brightness;
	color.g = color.g * brightness;
	color.b = color.b * brightness;
	
	light = new_point_light(position, color);
	add_light_to_world(world, light);
	destroy_2d((void**)tokens);
	return (1);
}

int parse_sphere(char *line, t_world *world)
{
	char **tokens;
	t_tuple center;
	float radius;
	t_rgb color;

	tokens = ft_split(line, ' ');
	
	// Validate parameter count (sp center diameter color)
	if (!validate_parameter_count(tokens, "Sphere", 4))
	{
		destroy_2d((void**)tokens);
		return (0);
	}
	
	// Parse center position
	center = parse_tuple(tokens[1], 1);
	
	// Parse and validate diameter/radius (must be positive)
	radius = parse_float(tokens[2]);
	if (radius <= 0)
	{
		printf("Error: Sphere diameter must be positive, got %.2f\n", radius);
		destroy_2d((void**)tokens);
		return (0);
	}
	
	// Parse and validate RGB
	if (!validate_and_parse_rgb(tokens[3], &color))
	{
		printf("Error: Invalid RGB values in sphere: '%s'\n", tokens[3]);
		destroy_2d((void**)tokens);
		return (0);
	}
	
	t_sphere *sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		printf("Error: Memory allocation failed for sphere\n");
		destroy_2d((void**)tokens);
		return (0);
	}
	
	*sphere = new_sphere(point(0, 0, 0), 1.0);
	t_object obj = new_object(SPHERE, sphere);
	obj.material.color = color;
	set_object_transform(&obj, scaling_matrix(radius, radius, radius));
	set_object_transform(&obj, translation_matrix(center.x, center.y, center.z));
	
	add_object_to_world(world, obj);
	destroy_2d((void**)tokens);
	return (1);
}

int parse_cylinder(char *line, t_world *world)
{
    char **tokens;
    t_tuple center;
    t_tuple orientation;
    float diameter;
    float height;
    t_rgb color;
    t_bool closed;
    t_object obj;

    printf("[DEBUG] Parsing line: %s\n", line);

    tokens = ft_split(line, ' ');
    
    // Validate parameter count (cy center orientation diameter height color closed)
    if (!validate_parameter_count(tokens, "Cylinder", 7))
    {
        destroy_2d((void**)tokens);
        return (0);
    }

    // Parse center position
    center = parse_tuple(tokens[1], 1);
    printf("[DEBUG] Center: (%f, %f, %f)\n", center.x, center.y, center.z);

    // Parse and normalize orientation vector
    orientation = normalize_vector(parse_tuple(tokens[2], 0));
    printf("[DEBUG] Orientation: (%f, %f, %f)\n", orientation.x, orientation.y, orientation.z);

    // Parse and validate diameter (must be positive)
    diameter = parse_float(tokens[3]);
    if (diameter <= 0)
    {
        printf("Error: Cylinder diameter must be positive, got %.2f\n", diameter);
        destroy_2d((void**)tokens);
        return (0);
    }
    
    // Parse and validate height (must be positive)
    height = parse_float(tokens[4]);
    if (height <= 0)
    {
        printf("Error: Cylinder height must be positive, got %.2f\n", height);
        destroy_2d((void**)tokens);
        return (0);
    }
    printf("[DEBUG] Diameter: %f, Height: %f\n", diameter, height);

    // Parse and validate RGB
    if (!validate_and_parse_rgb(tokens[5], &color))
    {
        printf("Error: Invalid RGB values in cylinder: '%s'\n", tokens[5]);
        destroy_2d((void**)tokens);
        return (0);
    }
    printf("[DEBUG] Color: (%f, %f, %f)\n", color.r, color.g, color.b);

    // Parse closed flag
    closed = ft_atoi(tokens[6]) != 0;
    printf("[DEBUG] Closed: %d\n", closed);

    obj = new_cylinder_object(center, orientation, diameter, height, color, closed);
    printf("[DEBUG] Cylinder object created\n");

    add_object_to_world(world, obj);
    destroy_2d((void**)tokens);
    printf("[DEBUG] Tokens freed and object added to world\n");

    return 1;
}

int parse_plane(char *line, t_world *world)
{
    char **tokens;
    t_tuple point;
    t_tuple normal;
    t_rgb color;
    t_object obj;

    tokens = ft_split(line, ' ');
    if (!validate_parameter_count(tokens, "Plane", 4))
    {
        destroy_2d((void**)tokens);
        return 0;
    }

    // Ponto do plano
    point = parse_tuple(tokens[1], 1);

    // Normal do plano
    normal = parse_tuple(tokens[2], 0);
    if (fabs(normal.x) > 1.0 || fabs(normal.y) > 1.0 || fabs(normal.z) > 1.0)
    {
        printf("Error: Plane normal must be in [-1,1]\n");
        destroy_2d((void**)tokens);
        return 0;
    }
    normal = normalize_vector(normal);

    // Cor do plano
    if (!validate_and_parse_rgb(tokens[3], &color))
    {
        printf("Error: Invalid RGB values for plane\n");
        destroy_2d((void**)tokens);
        return 0;
    }

    // Criar plano
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
    {
        printf("Error: malloc plane\n");
        destroy_2d((void**)tokens);
        return 0;
    }
    plane = new_plane(point, normal);

    // Criar objeto
    obj = new_object(PLANE, plane);
    obj.material.color = color;

    add_object_to_world(world, obj);

    destroy_2d((void**)tokens);
    return 1;
}
