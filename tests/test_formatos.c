int	close_window(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307) // ESC
		exit(0);
	return (0);
}


int	handle_key(int keycode, void *param)
{
	if (keycode == 65307) // ESC
		close_window(keycode, param);
	return (0);
}
t_object *create_test_scene(void)
{
    t_sphere *s;
    t_plane *p;
    t_cylinder *c;

    t_object *obj_sphere;
    t_object *obj_plane;
    t_object *obj_cyl;

    // Esfera
    s = malloc(sizeof(t_sphere));
    if (!s) return NULL;
    s->center = vec3(0, 0, 5);
    s->radius = 1.0;
    s->color = (t_color){255, 0, 0};
    obj_sphere = malloc(sizeof(t_object));
    if (!obj_sphere) return NULL;
    obj_sphere->type = SPHERE;
    obj_sphere->shape = s;
    obj_sphere->next = NULL;

    // Plano
    p = malloc(sizeof(t_plane));
    if (!p) return NULL;
    p->point = vec3(0, -1, 0);
    p->normal = vec3_normalize(vec3(0, 1, 0));
    p->color = (t_color){0, 255, 0};
    obj_plane = malloc(sizeof(t_object));
    if (!obj_plane) return NULL;
    obj_plane->type = PLANE;
    obj_plane->shape = p;
    obj_plane->next = NULL;

    obj_sphere->next = obj_plane;

    // Cilindro
    c = malloc(sizeof(t_cylinder));
    if (!c) return NULL;
    c->center = vec3(2, 0, 5);
    c->axis = vec3_normalize(vec3(0, 1, 0));
    c->radius = 0.5;
    c->height = 2.0;
    c->color = (t_color){0, 0, 255};
    obj_cyl = malloc(sizeof(t_object));
    if (!obj_cyl) return NULL;
    obj_cyl->type = CYLINDER;
    obj_cyl->shape = c;
    obj_cyl->next = NULL;

    obj_plane->next = obj_cyl;

    return obj_sphere; // Cabeça da lista
}


int main(void)
{
    t_mlx mlx;
    t_camera cam;
    t_object *scene;

    if (!mlx_init_all(&mlx, WIDTH, HEIGHT))
    {
        perror("mlx_init");
        return (1);
    }

    init_camera(&cam, WIDTH, HEIGHT);
    scene = create_test_scene();
    if (!scene)
    {
        fprintf(stderr, "Failed to create scene\n");
        return (1);
    }

    render_scene(scene, &cam, &mlx);

    mlx_hook(mlx.win_ptr, 2, 1L << 0, close_window, NULL);
    mlx_hook(mlx.win_ptr, 17, 0, close_window, NULL);

    mlx_loop(mlx.mlx_ptr);

    return (0);
}
