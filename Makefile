NAME = miniRT

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes -Iincludes/minilibx -Iutils/libft

SRC = \
    src/main.c \
    src/parser/parse_rt_file.c \
    src/utils/log.c \
    src/utils/validate.c \
    src/utils/color_utils.c \
    src/parser/parse_utils.c \
	src/parser/parse_utils_1.c \
    src/parser/parse_utils_2.c \
	src/parser/parse_ambient.c \
	src/parser/parse_objects.c \
	src/parser/parse_lights.c \
	src/parser/parse_camera.c \
    src/ray/hit.c \
    src/ray/ray.c \
    src/utils/vec3_more.c \
    src/utils/vec3_ops.c \
    src/objects/cylinder.c \
	src/objects/objects_utils.c \
    src/objects/plane.c \
    src/objects/sphere.c \
    src/mlx/mlx_utils.c \
    src/objects/intersection.c \
    src/core/camera.c \
    src/core/renderer.c \
    src/shading/ambient.c \
	src/shading/diffuse.c \
	src/shading/shadow.c \
	src/shading/specular.c \
	src/shading/lighting.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = utils/libft
MLX_DIR = includes/minilibx

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

bonus: all
