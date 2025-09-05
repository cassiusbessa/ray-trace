#include "../../includes/miniRT.h"


int parse_ambient(char *line, t_world *world)
{
	char **tokens;
	float ratio;
	t_rgb color;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Ambient light", 3))
		return (destroy_2d((void**)tokens), 0);
	ratio = parse_float(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (destroy_2d((void**)tokens), 0);
	world->ambient.ratio = ratio;
	if (!validate_and_parse_rgb(tokens[2], &color))
		return (destroy_2d((void**)tokens), 0);
	world->ambient.color = color;
	destroy_2d((void**)tokens);
	return (1);
}

int parse_camera(char *line, t_camera *camera)
{
	char **tokens;
	float fov;
	t_tuple position, direction;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Camera", 4))
		return (destroy_2d((void**)tokens), 0);
	position = parse_tuple(tokens[1], 1);
	direction = normalize_vector(parse_tuple(tokens[2], 0));
	fov = parse_float(tokens[3]);
	if (fov <= 0 || fov >= 180)
		return (destroy_2d((void**)tokens), 0);
	*camera = new_camera(WIDTH, HEIGHT, fov * M_PI / 180.0);
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
	if (!validate_parameter_count(tokens, "Light", 4))
		return (destroy_2d((void**)tokens), 0);
	position = parse_tuple(tokens[1], 1);
	brightness = parse_float(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (destroy_2d((void**)tokens), 0);
	if (!validate_and_parse_rgb(tokens[3], &color))
		return (destroy_2d((void**)tokens), 0);
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
	t_object obj;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Sphere", 4))
		return (destroy_2d((void**)tokens), 0);
	center = parse_tuple(tokens[1], 1);
	radius = parse_float(tokens[2]);
	if (radius <= 0)
		return (destroy_2d((void**)tokens), 0);
	if (!validate_and_parse_rgb(tokens[3], &color))
		return (destroy_2d((void**)tokens), 0);
	t_sphere *sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (destroy_2d((void**)tokens), 0);
	*sphere = new_sphere(point(0, 0, 0), 1.0);
	obj = new_object(SPHERE, sphere);
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

    tokens = ft_split(line, ' ');
    if (!validate_parameter_count(tokens, "Cylinder", 7))
        return (destroy_2d((void**)tokens), 0);
    center = parse_tuple(tokens[1], 1);
    orientation = normalize_vector(parse_tuple(tokens[2], 0));
    diameter = parse_float(tokens[3]);
    if (diameter <= 0)
        return (destroy_2d((void**)tokens), 0);
    height = parse_float(tokens[4]);
    if (height <= 0)
        return (destroy_2d((void**)tokens), 0);
    if (!validate_and_parse_rgb(tokens[5], &color))
        return (destroy_2d((void**)tokens), 0);
    closed = ft_atoi(tokens[6]) != 0;
    obj = new_cylinder_object(center, orientation, diameter, height, color, closed);
    add_object_to_world(world, obj);
    destroy_2d((void**)tokens);
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
        return (destroy_2d((void**)tokens), 0);
    point = parse_tuple(tokens[1], 1);
    normal = parse_tuple(tokens[2], 0);
    if (fabs(normal.x) > 1.0 || fabs(normal.y) > 1.0 || fabs(normal.z) > 1.0)
        return (destroy_2d((void**)tokens), 0);
    normal = normalize_vector(normal);
    if (!validate_and_parse_rgb(tokens[3], &color))
        return (destroy_2d((void**)tokens), 0);
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
        return (destroy_2d((void**)tokens), 0);
    plane = new_plane(point, normal);
    obj = new_object(PLANE, plane);
    obj.material.color = color;
    add_object_to_world(world, obj);
    destroy_2d((void**)tokens);
    return 1;
}
