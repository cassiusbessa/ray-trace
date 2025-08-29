# ===========================================
# Makefile para projeto miniRT (Linux/WSL)
# ===========================================

# Compilador e flags
CC      = cc -g
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

# Diretórios
TUPLE_DIR        = src/tuple
VECTOR_DIR       = src/vector
RGB_DIR          = src/rgb
CANVAS_DIR       = src/canvas
MATRIX_DIR       = src/matrix
MLX_DIR          = src/mlx_adapter
TRANSF_DIR       = src/transformation
RAY_DIR          = src/ray
SPHERE_DIR       = src/sphere
INTERSECTION_DIR = src/intersection
OBJS_DIR         = src/objects
NORMAL_DIR       = src/normal
REFLECT_DIR      = src/reflect
LIGHT_DIR        = src/light
MATERIAL_DIR     = src/material
WORLD_DIR        = src/world
COMPUTATION_DIR  = src/computation
CAMERA_DIR       = src/camera
UTILS_DIR        = src/utils
INCLUDE_DIR      = include
LIBFT_DIR        = utils/libft
MINILIBX_DIR     = includes/minilibx-linux

TESTS_DIR        = tests

# Nome do executável
MINIRT           = miniRT

# Bibliotecas
LIBFT            = $(LIBFT_DIR)/libft.a
MINILIBX         = $(MINILIBX_DIR)/libmlx_Linux.a

# Arquivos fontes
SRCS = main.c \
       src/camera/free_camera.c \
       $(TUPLE_DIR)/tuple.c \
       $(TUPLE_DIR)/tuple_utils.c \
       $(TUPLE_DIR)/vector.c \
       $(RGB_DIR)/rgb.c \
       $(RGB_DIR)/rgb_utils.c \
       $(CANVAS_DIR)/canvas.c \
       $(MATRIX_DIR)/matrix.c \
       $(MATRIX_DIR)/matrix_utils.c \
       $(MATRIX_DIR)/matrix_multiply.c \
       $(MATRIX_DIR)/matrix_rotate.c \
       $(MATRIX_DIR)/minor_matrix.c \
       $(MATRIX_DIR)/cofactor_matrix.c \
       $(MATRIX_DIR)/matrix_determinant.c \
       $(MATRIX_DIR)/matrix_invertible.c \
       $(MLX_DIR)/open_mlx_screen.c \
       $(MLX_DIR)/canvas_to_mlx_image.c \
       $(TRANSF_DIR)/translation.c \
       $(TRANSF_DIR)/scaling.c \
       $(TRANSF_DIR)/rotation.c \
       $(TRANSF_DIR)/shearing.c \
       $(TRANSF_DIR)/view_transform.c \
       src/transformations/chain_transformations.c \
       $(RAY_DIR)/ray.c \
       $(RAY_DIR)/ray_utils.c \
       $(SPHERE_DIR)/sphere.c \
       $(INTERSECTION_DIR)/intersection.c \
       $(INTERSECTION_DIR)/intersection_list.c \
       $(INTERSECTION_DIR)/hit.c \
       $(OBJS_DIR)/object.c \
       $(NORMAL_DIR)/normal.c \
       $(REFLECT_DIR)/reflect.c \
       $(LIGHT_DIR)/light.c \
       $(LIGHT_DIR)/lighting.c \
       $(MATERIAL_DIR)/material.c \
       $(WORLD_DIR)/world.c \
       $(WORLD_DIR)/shade.c \
       $(COMPUTATION_DIR)/prepare_computation.c \
       $(CAMERA_DIR)/camera.c \
       $(UTILS_DIR)/solve_quadratic.c \
       src/thick.c

# Objetos
OBJS = $(SRCS:.c=.o)

# ===========================================
# Regras
# ===========================================


# Compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Executável principal
$(MINIRT): $(OBJS)
	@make -C $(LIBFT_DIR)
	@echo "Compilando MiniLibX..."
	@make -C $(MINILIBX_DIR) all
	$(CC) $(OBJS) $(LIBFT) $(MINILIBX) -o $(MINIRT) -I$(INCLUDE_DIR) -I$(MINILIBX_DIR) -lXext -lX11 -lreadline -lm
	@printf "\e[92;5;118m    - Executable ready.\n\e[0m"

# Compilar tudo
all: $(MINIRT)

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all ./$(MINIRT)


# Testes
test:
	@$(MAKE) -C $(TESTS_DIR) run

run: all
	@./$(MINIRT)

test_leaks:
	@$(MAKE) -C $(TESTS_DIR) leaks

# Limpeza
clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(TESTS_DIR)
	$(RM) $(OBJS)
	@printf "\e[93;5;226m    - Objects removed.\n\e[0m"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(TESTS_DIR)
	$(RM) $(MINIRT)
	@printf "\e[93;5;226m    - Executable removed.\n\e[0m"

re: fclean all

.PHONY: all clean fclean re test test_leaks
