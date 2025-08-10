miniRT/
├── includes/
│   ├── minilibx/              # Código fonte da MiniLibX (clonado do Git oficial)
│   └── miniRT.h               # Header principal com structs, includes e protótipos
│
├── scenes/                    # Exemplos de arquivos .rt para testes
│
├── src/
│   ├── core/                  # Módulo principal: câmera, renderização, raytracing e iluminação
│   │   ├── camera.c           # Funções: init_camera, camera_ray
│   │   
|   ├── shading/
|   |   ├── ambient.c       # apply_ambient_light
|   |   ├── diffuse.c       # apply_diffuse_light
|   |   ├── shadow.c        # create_shadow_ray, in_shadow
|   |   ├── specular.c      # calculate_specular
|   |   └── lighting.c      # calculate_lighting
|   |   
│   ├── mlx/                   # Funções relacionadas à MiniLibX e eventos
│   │   └── mlx_utils.c        # mlx_init_all, close_window, outros utilitários
│   │
│   ├── objects/               # Implementação dos objetos e suas interseções
│   │   ├── cylinder.c         # intersect_cylinder, helpers
│   │   ├── intersections.c    # intersect_object
│   │   ├── plane.c            # intersect_plane
│   │   └── sphere.c           # intersect_sphere, solve_quadratic
│   │
│   ├── parser/                # Parser do arquivo .rt
│   │   ├── parse.c            # parse_rt_file
│   │   ├── parse_lighting.c   # parse_ambient, parse_point_light (vazio ou implementar)
│   │   ├── parse_utils.c      # parse_color, parse_vec3
│   │   └── parse_utils_1.c    # count_tokens, ft_atof, parse_float, ft_free_split
│   │
│   ├── ray/                   # Funções para raios e cálculo de interseção
│   │   ├── hit.c              # compute_hit_point, compute_normal
│   │   └── ray.c              # ray_new, ray_at
│   │
│   ├── renderer/              # Funções auxiliares para renderização
│   │   └── object_hit.c       # closest_hit (mover de core/renderer.c)
│   │
│   ├── utils/                 # Funções auxiliares gerais
│   │   ├── color_utils.c      # add_colors, clamp_color, color_to_int, make_color
│   │   ├── log.c              # print_error, log_debug
│   │   ├── validation.c       # check_range, is_in_range
│   │   ├── vec3_more.c        # length, normalize, cross
│   │   └── vec3_ops.c         # add, sub, dot, scale
│   │
│   └── main.c                 # Ponto de entrada do programa
│
├── utils/
│   └── libft/                 # Sua biblioteca libft (obrigatória)
│
└── Makefile                   # Script para compilar e limpar o projeto




Show! Vamos iniciar a Sprint 5 COMPLETA para seu miniRT, com tudo que você precisa para renderizar a cena básica, criando câmera, inicializando MiniLibX, gerando raios por pixel, usando o closest hit da Sprint 4, pintando na janela e muito mais.

Vou entregar em etapas organizadas, arquivos separados, explicações detalhadas, e ao final dicas para compilar e rodar.

Sprint 5 Completa — Renderização Básica e Closest Hit
1) Atualização do include/miniRT.h
Vamos acrescentar as structs da câmera e do MLX, protótipos das funções novas, e macros necessárias.

c
Copiar
Editar
#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"

/* --- macros --- */
# define EPS 1e-6
# define INF 1e30

/* --- tipos básicos --- */
typedef struct s_vec3 {
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_ray {
	t_vec3 origin;
	t_vec3 dir;
}	t_ray;

typedef struct s_color {
	int r; int g; int b;
}	t_color;

/* --- objetos --- */
typedef enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_sphere {
	t_vec3 center;
	double radius;
	t_color color;
}	t_sphere;

typedef struct s_plane {
	t_vec3 point;
	t_vec3 normal;
	t_color color;
}	t_plane;

typedef struct s_cylinder {
	t_vec3 center;
	t_vec3 axis;
	double radius;
	double height;
	t_color color;
}	t_cylinder;

typedef struct s_object {
	t_obj_type type;
	void *shape;
	struct s_object *next;
}	t_object;

typedef struct s_intersection {
	double t;
	t_vec3 point;
	t_vec3 normal;
	t_object *object;
}	t_intersection;

/* --- câmera --- */
typedef struct s_camera {
	t_vec3 origin;
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;
	double fov; // graus
	int width;
	int height;
}	t_camera;

/* --- MiniLibX --- */
typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
	int width;
	int height;
}	t_mlx;

/* --- vetores --- */
t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* --- ray --- */
t_ray	ray_new(t_vec3 orig, t_vec3 dir);
t_vec3	ray_at(t_ray r, double t);

/* --- interseções --- */
int		intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_plane(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_cylinder(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_object(t_ray *ray, t_object *obj, t_intersection *out);

/* --- hit utils --- */
t_vec3	compute_hit_point(t_ray *ray, double t);
t_vec3	compute_normal(t_object *obj, t_vec3 point);

/* --- render --- */
void	render_scene(t_object *scene, t_camera *cam, t_mlx *mlx);
int		closest_hit(t_ray *ray, t_object *scene, t_intersection *out);
t_ray	camera_ray(t_camera *cam, int px, int py);

/* --- utils mlx --- */
int		mlx_init_all(t_mlx *mlx, int width, int height);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

/* --- input / events --- */
int		close_win(int keycode, void *param);

#endif
2) Código fonte da Sprint 5
src/utils/vec3_ops.c e vec3_more.c
Use exatamente os códigos da Sprint 4. Repito aqui só para completar.

src/ray/ray.c
Mesmo da Sprint 4.

src/objects/*.c
Mesmos dos 3 objetos da Sprint 4.

Novo arquivo: src/renderer/renderer.c
c
Copiar
Editar
#include "miniRT.h"

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

int closest_hit(t_ray *ray, t_object *scene, t_intersection *out)
{
	t_object *cur = scene;
	t_intersection tmp;
	int hit_any = 0;
	double closest_t = INF;

	while (cur)
	{
		if (intersect_object(ray, cur, &tmp))
		{
			if (tmp.t > EPS && tmp.t < closest_t)
			{
				closest_t = tmp.t;
				*out = tmp;
				hit_any = 1;
			}
		}
		cur = cur->next;
	}
	return (hit_any);
}

void render_scene(t_object *scene, t_camera *cam, t_mlx *mlx)
{
	int x, y;
	t_ray ray;
	t_intersection hit;
	int color;
	t_color col;

	for (y = 0; y < cam->height; y++)
	{
		for (x = 0; x < cam->width; x++)
		{
			ray = camera_ray(cam, x, y);
			if (closest_hit(&ray, scene, &hit))
			{
				/* pega cor do objeto conforme tipo */
				if (hit.object->type == SPHERE)
					col = ((t_sphere *)hit.object->shape)->color;
				else if (hit.object->type == PLANE)
					col = ((t_plane *)hit.object->shape)->color;
				else if (hit.object->type == CYLINDER)
					col = ((t_cylinder *)hit.object->shape)->color;
				else
					col = (t_color){0, 0, 0};

				color = (col.r << 16) | (col.g << 8) | col.b;
			}
			else
				color = 0x000000; /* fundo preto */

			put_pixel(mlx, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
Novo arquivo: src/renderer/camera.c
c
Copiar
Editar
#include "miniRT.h"
#include <math.h>

t_ray camera_ray(t_camera *cam, int px, int py)
{
	double aspect = (double)cam->width / (double)cam->height;
	double fov_adjust = tan((cam->fov * 0.5) * (M_PI / 180.0));
	double x = (2 * ((px + 0.5) / cam->width) - 1) * aspect * fov_adjust;
	double y = (1 - 2 * ((py + 0.5) / cam->height)) * fov_adjust;

	t_vec3 dir = vec3_add(vec3_add(vec3_scale(cam->right, x), vec3_scale(cam->up, y)), cam->forward);
	dir = vec3_normalize(dir);

	return (ray_new(cam->origin, dir));
}
Novo arquivo: src/utils/mlx_utils.c
c
Copiar
Editar
#include "miniRT.h"
#include <mlx.h>

int mlx_init_all(t_mlx *mlx, int width, int height)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, "miniRT");
	if (!mlx->win_ptr)
		return (0);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
	if (!mlx->img_ptr)
		return (0);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
	if (!mlx->img_data)
		return (0);
	mlx->width = width;
	mlx->height = height;
	return (1);
}

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
Novo arquivo: src/main.c
c
Copiar
Editar
#include "miniRT.h"
#include <mlx.h>
#include <stdlib.h>

int close_win(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(0);
	return (0);
}

int main(void)
{
	t_mlx mlx;
	t_camera cam;
	t_object *scene = NULL;
	t_sphere *s;
	t_plane *p;
	t_cylinder *c;

	/* Inicializa MLX e janela */
	if (!mlx_init_all(&mlx, 800, 600))
	{
		perror("mlx init");
		return (1);
	}

	/* Inicializa câmera */
	cam.origin = vec3(0, 0, 0);
	cam.forward = vec3_normalize(vec3(0, 0, 1));
	cam.up = vec3_normalize(vec3(0, 1, 0));
	cam.right = vec3_cross(cam.forward, cam.up);
	cam.fov = 60;
	cam.width = 800;
	cam.height = 600;

	/* Cria objetos manualmente */
	/* Esfera */
	s = malloc(sizeof(t_sphere));
	if (!s)
		return (1);
	s->center = vec3(0, 0, 5);
	s->radius = 1.0;
	s->color = (t_color){255, 0, 0};

	t_object *obj_sphere = malloc(sizeof(t_object));
	if (!obj_sphere)
		return (1);
	obj_sphere->type = SPHERE;
	obj_sphere->shape = s;
	obj_sphere->next = NULL;
	scene = obj_sphere;

	/* Plano */
	p = malloc(sizeof(t_plane));
	if (!p)
		return (1);
	p->point = vec3(0, -1, 0);
	p->normal = vec3_normalize(vec3(0, 1, 0));
	p->color = (t_color){0, 255, 0};

	t_object *obj_plane = malloc(sizeof(t_object));
	if (!obj_plane)
		return (1);
	obj_plane->type = PLANE;
	obj_plane->shape = p;
	obj_plane->next = NULL;
	obj_sphere->next = obj_plane;

	/* Cilindro */
	c = malloc(sizeof(t_cylinder));
	if (!c)
		return (1);
	c->center = vec3(2, 0, 5);
	c->axis = vec3_normalize(vec3(0, 1, 0));
	c->radius = 0.5;
	c->height = 2.0;
	c->color = (t_color){0, 0, 255};

	t_object *obj_cyl = malloc(sizeof(t_object));
	if (!obj_cyl)
		return (1);
	obj_cyl->type = CYLINDER;
	obj_cyl->shape = c;
	obj_cyl->next = NULL;
	obj_plane->next = obj_cyl;

	/* Renderiza a cena */
	render_scene(scene, &cam, &mlx);

	/* Configura eventos para fechar */
	mlx_hook(mlx.win_ptr, 2, 1L << 0, close_win, NULL);    /* ESC tecla */
	mlx_hook(mlx.win_ptr, 17, 0, close_win, NULL);         /* clique fechar janela */

	mlx_loop(mlx.mlx_ptr);

	return (0);
}
Como compilar
Crie um Makefile (se quiser posso montar para você) com estas regras básicas:

makefile
Copiar
Editar
NAME = miniRT
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iutils/libft -lm
MLX_FLAGS = -lmlx -lXext -lX11 -lm

SRC = src/main.c \
	  src/utils/vec3_ops.c \
	  src/utils/mlx_utils.c \
	  src/ray/ray.c \
	  src/objects/sphere.c \
	  src/objects/plane.c \
	  src/objects/cylinder.c \
	  src/renderer/renderer.c \
	  src/renderer/camera.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
Teste rápido
Compile com make

Rode ./miniRT

Deve abrir janela 800x600 com uma esfera vermelha, plano verde, cilindro azul

Cores simples, sem luz por enquanto

Saia com ESC ou fechar janela

Aula rápida dentro da Sprint 5
MiniLibX: Criamos uma janela, uma imagem, e manipulamos pixels via ponteiro.

Câmera: Vimos como montar o raio por pixel, calculando direções a partir do FOV e vetores da câmera.

Closest hit: Buscamos o ponto mais próximo que o raio atinge, iterando sobre todos os objetos.

Render loop: Iteramos cada pixel da tela, geramos um raio, encontramos o objeto mais próximo e pintamos o pixel com a cor do objeto.

Estruturas: Usamos t_camera para armazenar parâmetros da câmera, e t_mlx para armazenar dados da MiniLibX.

Se quiser posso ajudar a quebrar isso em etapas ainda menores, ou partir para:

eu gostaria, mas queria lembra que vc esta saindo do escopo do projeto, outra coisa ja chegamos nessa formação de miniRT, porem precisa ser organizada e limpa, claro e incluindo as novas que vc vai ensinar na sprint 5

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
#include "mlx.h"

# include "libft.h"

// Definições iniciais
# define WIDTH 800
# define HEIGHT 600
# define TITLE "miniRT"

# define EPS 1e-6
# define INF 1e30

// Structs básicas (iremos expandir depois)
typedef struct s_vec3 {
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_color {
	float r;
	float g;
	float b;
} t_color;


typedef struct s_ray {
	t_vec3 origin;
	t_vec3 dir; /* deve ser normalizado */
}	t_ray;

/* objetos */
typedef enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_sphere {
	t_vec3 center;
	double radius;
	t_color color;
}	t_sphere;

typedef struct s_plane {
	t_vec3 point;
	t_vec3 normal; /* deve ser normalizado */
	t_color color;
}	t_plane;

typedef struct s_cylinder {
	t_vec3 center;  /* centro (ponto no meio do cilindro) */
	t_vec3 axis;    /* vetor direção (deve ser normalizado) */
	double radius;
	double height;
	t_color color;
}	t_cylinder;

typedef struct s_object {
	t_obj_type type;
	void *shape;           /* aponta para t_sphere / t_plane / t_cylinder */
	struct s_object *next; /* lista ligada para cena */
}	t_object;

typedef struct s_intersection {
	double t;
	t_vec3 point;
	t_vec3 normal;
	t_object *object;
}	t_intersection;

typedef struct s_camera {
	t_vec3 origin;
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;
	double fov; // em graus
	int width;
	int height;
}	t_camera;

typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
	int width;
	int height;
}	t_mlx;



//-----------------------------------
// Funções de validação e logging
//-----------------------------------

void	print_error(char *message, char **to_free);
void	log_debug(char *msg);
void	check_range(float value, float min, float max, char *msg, char **to_free);

///-----------------------------------
// Funções de Parsing
///-----------------------------------

int	parse_rt_file(char *filename);

float	parse_float(char *str);
t_vec3	parse_vec3(char *str);
t_color	parse_color(char *str);
float	ft_atof(const char *nptr);

void    ft_free_split(char **tokens);
int	count_tokens(char **tokens);


/* --- vetores --- */
t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);

/* src/utils/vec3_more.c */
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

/* --- ray --- */
t_ray	ray_new(t_vec3 orig, t_vec3 dir);
t_vec3	ray_at(t_ray r, double t);

/* --- interseções por objeto --- */
/* src/objects */
int		intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_plane(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_cylinder(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_object(t_ray *ray, t_object *obj, t_intersection *out);

/* hit utils (calcular ponto e normal) */
/* src/ray/hit.c */
t_vec3	compute_hit_point(t_ray *ray, double t);
t_vec3	compute_normal(t_object *obj, t_vec3 point);

#endif





Perfeito! Vamos quebrar a Sprint 7 em várias pequenas sprints e tarefas minuciosas para garantir um progresso estruturado, fácil de acompanhar e com entregas contínuas. Cada mini-sprint terá objetivos claros, descrições técnicas e sugestões de implementação.

Sprint 7 - Desenvolvimento Modular e Progressivo
Mini-Sprint 7.1 — Suporte a múltiplas fontes de luz
Objetivo
Modificar a estrutura de cena para armazenar múltiplas luzes pontuais.

Adaptar a função calculate_lighting para somar a contribuição de todas as luzes.

Atualizar o parser para ler múltiplas definições de luzes no arquivo .rt.

Tarefas
Alterar estrutura de cena (t_scene)

Substituir o campo único t_point_light point_light por um vetor/lista dinâmica de luzes (ex.: t_point_light *point_lights + int n_point_lights).

Gerenciar alocação dinâmica e liberação dessas luzes.

Atualizar calculate_lighting

Modificar para iterar por todas as luzes e somar as contribuições (difusa + especular) considerando sombras para cada luz.

Manter o cálculo da luz ambiente separado e somar uma única vez.

Adaptar parser

Permitir ler várias linhas que definem luzes pontuais no arquivo .rt.

Para cada linha, alocar e armazenar a luz no vetor da cena.

Testes

Criar cenas .rt com 2 ou 3 luzes para validar o sombreamento múltiplo.

Testar sombras múltiplas e mistura correta de luzes.

Mini-Sprint 7.2 — Implementação de sombras para múltiplas luzes
Objetivo
Garantir que a função de sombra (in_shadow) funcione para todas as luzes.

Suportar sombras parciais (no futuro).

Tarefas
Sombras para múltiplas luzes

Modificar chamadas de sombra para serem feitas para cada luz no loop de iluminação.

Se ponto estiver em sombra para determinada luz, ignorar contribuição difusa e especular dessa luz, mas somar luz ambiente normalmente.

Preparação para sombras parciais (pensar em futuro)

Criar estrutura que permita futuramente armazenar transparência em objetos.

Planejar dados para fatores de penumbra (soft shadows).

Testes

Criar cenas com objetos entre luzes e superfícies para validar sombras múltiplas.

Testar se a luz ambiente permanece constante mesmo em sombra.

Mini-Sprint 7.3 — Materiais avançados: reflexão especular variável
Objetivo
Adicionar propriedades materiais para objetos.

Permitir configurar intensidade especular por objeto.

Tarefas
Criar estrutura de materiais

Novo struct t_material com pelo menos: cor base, coeficiente especular (float), brilho (shininess).

Associar material a cada objeto (em vez de só cor simples).

Adaptar cálculo especular

Usar coeficiente e brilho do material no cálculo.

Adaptar parser para permitir definir materiais.

Testes

Testar objetos com diferentes especulares (brilho, intensidade).

Verificar se reflexões se comportam conforme esperado.

Mini-Sprint 7.4 — Transparência e refração (índice de refração)
Objetivo
Implementar suporte básico a materiais transparentes e cálculo de refração.

Simular raios refratados.

Tarefas
Adicionar propriedades de transparência e índice de refração ao material

Campo float transparency e float ior (índice de refração).

Implementar cálculo de raio refratado

Função para calcular vetor refratado baseado no índice de refração (Snell).

Adaptar o pipeline do raytracer para lançar raios refratados (recursão limitada).

Testes

Criar objetos parcialmente transparentes.

Testar se refração visual aparece no render.

Mini-Sprint 7.5 — Texturas e padrões
Objetivo
Implementar suporte a texturas básicas (padrões de cor).

Aplicar texturas aos objetos.

Tarefas
Criar interface para texturas

Padrões simples: listras, xadrez, gradiente.

Associar textura ao material.

Mapeamento UV simples para esferas e planos

Funções que calculam coordenadas de textura.

Testes

Testar aplicação correta de padrões nos objetos.

Validar com e sem texturas.

Mini-Sprint 7.6 — Melhorias em performance
Objetivo
Otimizar o render para ganhar velocidade.

Tarefas
Multithreading

Implementar paralelização da renderização (p.ex., por linhas da tela).

Estruturas de aceleração

BVH (Bounding Volume Hierarchy) simples para acelerar testes de interseção.

Testes

Medir tempo antes/depois.

Validar que resultados continuam corretos.

Mini-Sprint 7.7 — Anti-aliasing e interface de usuário
Objetivo
Suavizar a imagem com anti-aliasing básico.

Criar controles para movimentar câmera e alterar parâmetros em tempo real.

Tarefas
Anti-aliasing

Supersampling (múltiplos raios por pixel e média das cores).

Interface

Adicionar manipulação do teclado/mouse para mover a câmera.

Mostrar informações básicas na tela.

Mini-Sprint 7.8 — Parser e validação avançada
Objetivo
Melhorar o parser para lidar com erros e validar dados.

Suportar mais tipos de objetos e propriedades.

Tarefas
Validação robusta

Checagem rigorosa de formatos e valores.

Mensagens de erro amigáveis.

Novos objetos

Adicionar suporte a cones, cubos, planos texturizados, etc.

Testes

Arquivos .rt variados e complexos.










Adicionar texturas e padrões (7.5)

Otimizar performance com multithreading e BVH (7.6)

Adicionar anti-aliasing e interface (7.7)

Melhorar parser com validações avançadas (7.8)

