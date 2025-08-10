#include "miniRT.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	handle_key(int keycode, void *param)
{
	if (keycode == 65307) // ESC
		close_window(param);
	return (0);
}


/* helpers para criar objetos simples (alocam) */
static t_object *make_sphere(double cx, double cy, double cz, double r)
{
	t_sphere *s = malloc(sizeof(t_sphere));
	t_object *o = malloc(sizeof(t_object));
	if (!s || !o) exit(1);
	s->center = vec3(cx, cy, cz);
	s->radius = r;
	o->type = SPHERE;
	o->shape = s;
	o->next = NULL;
	return (o);
}

static t_object *make_plane(double px, double py, double pz, double nx, double ny, double nz)
{
	t_plane *p = malloc(sizeof(t_plane));
	t_object *o = malloc(sizeof(t_object));
	if (!p || !o) exit(1);
	p->point = vec3(px, py, pz);
	p->normal = vec3_normalize(vec3(nx,ny,nz));
	o->type = PLANE;
	o->shape = p;
	o->next = NULL;
	return (o);
}

static t_object *make_cylinder(double cx, double cy, double cz, double ax, double ay, double az, double radius, double height)
{
	t_cylinder *c = malloc(sizeof(t_cylinder));
	t_object *o = malloc(sizeof(t_object));
	if (!c || !o) exit(1);
	c->center = vec3(cx,cy,cz);
	c->axis = vec3_normalize(vec3(ax,ay,az));
	c->radius = radius;
	c->height = height;
	o->type = CYLINDER;
	o->shape = c;
	o->next = NULL;
	return (o);
}

static void print_hit(const char *name, int hit, t_intersection *it, t_ray *ray)
{
	if (!hit)
	{
		printf("%s: no hit\n", name);
		return;
	}
	it->point = compute_hit_point(ray, it->t);
	it->normal = compute_normal(it->object, it->point);
	printf("%s: hit t=%.6f point=(%.3f,%.3f,%.3f) normal=(%.3f,%.3f,%.3f)\n",
		name, it->t, it->point.x, it->point.y, it->point.z,
		it->normal.x, it->normal.y, it->normal.z);
}

static void run_tests(void)
{
	t_ray ray = ray_new(vec3(0,0,0), vec3(0,0,1));
	t_intersection it;

	/* Sphere centered at (0,0,5) radius 1 => entering at z=4 => t≈4 */
	t_object *s = make_sphere(0,0,5,1);
	print_hit("Sphere", intersect_object(&ray, s, &it), &it, &ray);

	/* Plane at z=10 normal (0,0,1) => t=10 */
	t_object *p = make_plane(0,0,10, 0,0,1);
	print_hit("Plane", intersect_object(&ray, p, &it), &it, &ray);

	/* Cylinder centered at (0.5,0,10), axis (0,1,0), r=1, h=20
	   we expect two intersections, nearest t ≈ 10 - sqrt(0.75) ≈ 9.133975
	*/
	t_object *c = make_cylinder(0.5,0,10, 0,1,0, 1.0, 20.0);
	print_hit("Cylinder", intersect_object(&ray, c, &it), &it, &ray);

	/* liberar memoria (omito para brevidade) */
	
}


int	main(int argc, char **argv)
{
    void *mlx;
    void *win;

    if (argc != 2)
        print_error("Usage: ./miniRT <filename>\n", NULL);

    if(parse_rt_file(argv[1]))
        print_error("Failed to parse the RT file\n", NULL);

    // Chamar run_tests para imprimir os testes no console
    run_tests();

        
    mlx = mlx_init();
    if (!mlx)
        print_error("Error initializing MLX\n", NULL);

    log_debug("Inicializando miniRT");

    win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
    if (!win)
        print_error("Error creating window\n", NULL);

    mlx_hook(win, 17, 0, close_window, NULL);    // Fecha janela no X
    mlx_key_hook(win, handle_key, NULL);         // Fecha com ESC

    mlx_loop(mlx);
    return (0);
}
