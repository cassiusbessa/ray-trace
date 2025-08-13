# Definição de variáveis
CC          = cc -g
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Caminhos
TUPLE_DIR   = src/tuple
VECTOR_DIR  = src/vector
RGB_DIR		= src/rgb
CANVAS_DIR  = src/canvas
MATRIX_DIR  = src/matrix
MLX_DIR		= src/mlx_adapter
INCLUDE_DIR = include
LIBFT_DIR   = utils/libft

TESTS_DIR   = tests

# Nome do executável
MINIRT      = miniRT

# Biblioteca auxiliar
LIBFT       = $(LIBFT_DIR)/libft.a

MINILIBX = minilibx-linux/libmlx_Linux.a

# Arquivos de fontes do miniRT
SRCS        = $(TUPLE_DIR)/tuple.c \
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
			  $(MLX_DIR)/open_mlx_screen.c \
			  $(MLX_DIR)/canvas_to_mlx_image.c \
			  src/thick.c

# Arquivos de objeto
OBJS         = $(SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar o miniRT
$(MINIRT): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C minilibx-linux
	$(CC) $(OBJS) $(LIBFT) $(MINILIBX) -o $(MINIRT) -Imlx_linux -lXext -lX11 -lreadline -lm
	@printf "\e[92;5;118m    - Executable ready.\n\e[0m"

all: $(MINIRT)

# Chamar Makefile de testes
test:
	@$(MAKE) -C $(TESTS_DIR) run

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

.PHONY: all clean fclean re test
