/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:11:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 22:33:31 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../includes/headers/parser.h"


static int handle_parse_error(const char *msg, char *line,
	t_parsed_scene *scene, int fd)
{
	printf("Error %s: %s\n", msg, line);
	free(line);
	free_parsed_scene(scene);
	close(fd);
	return (0);
}

int starts_with(const char *line, const char *prefix)
{
    while (*prefix)
    {
        if (*line != *prefix)
            return 0;
        line++;
        prefix++;
    }
    return 1;
}

static char *clean_line(char *line)
{
    int len;

    if (!line || line[0] == '\n' || line[0] == '#' || line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return (line);
}

static int dispatch_parse(char *line, t_parsed_scene *scene, int fd)
{
    if (starts_with(line, "A "))
    {
        if (!parse_ambient(line, scene->world))
            return (handle_parse_error("parsing ambient", line, scene, fd), 0);
    }
    else if (starts_with(line, "C "))
    {
        if (!parse_camera(line, &scene->camera))
            return (handle_parse_error("parsing camera", line, scene, fd), 0);
    }
    else if (starts_with(line, "L "))
    {
        if (!parse_light(line, scene->world))
            return (handle_parse_error("parsing light", line, scene, fd), 0);
    }
    else if (starts_with(line, "sp "))
    {
        if (!parse_sphere(line, scene->world))
            return (handle_parse_error("parsing sphere", line, scene, fd), 0);
    }
    else if (starts_with(line, "cy "))
    {
        if (!parse_cylinder(line, scene->world))
            return (handle_parse_error("parsing cylinder", line, scene, fd), 0);
    }
    else if (starts_with(line, "pl "))
    {
        if (!parse_plane(line, scene->world))
            return (handle_parse_error("parsing plane", line, scene, fd), 0);
    }
    else
    {
        printf("Error: Unknown element identifier in line: %s\n", line);
        free(line);
        free_parsed_scene(scene);
        close(fd);
        return (0);
    }
    return (1);
}

t_parsed_scene *parse_rt_file(const char *filename)
{
    int fd;
    char *line;
    t_parsed_scene *scene;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Cannot open file %s\n", filename), NULL);

    scene = malloc(sizeof(t_parsed_scene));
    if (!scene)
        return (close(fd), NULL);

    scene->world = malloc(sizeof(t_world));
    if (!scene->world)
        return (free(scene), close(fd), NULL);

    *(scene->world) = new_world();

    while ((line = get_next_line(fd)) != NULL)
    {
        line = clean_line(line);
        if (!line)
            continue;
        if (!dispatch_parse(line, scene, fd))
            return (NULL);
        free(line);
    }

    close(fd);
    printf("Successfully parsed file!\n");
    return scene;
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

	// Print objects
	printf("Objects (%d):\n", scene->world->objects->count);
	t_object_node *current_obj = scene->world->objects->head;
	int obj_index = 1;
	while (current_obj)
	{
		if (current_obj->object.type == SPHERE)
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
		else if (current_obj->object.type == PLANE)
		{
			t_plane *plane = (t_plane *)current_obj->object.data;
			printf("  Plane %d:\n", obj_index);
			printf("    Point: (%.2f, %.2f, %.2f)\n",
				plane->point.x, plane->point.y, plane->point.z);
			printf("    Normal: (%.2f, %.2f, %.2f)\n",
				plane->normal.x, plane->normal.y, plane->normal.z);
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