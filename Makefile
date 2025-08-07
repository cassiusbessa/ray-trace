# Nome do executável
NAME = miniRT

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Iincludes/minilibx-linux -Iutils/libft

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = includes/minilibx-linux

LIBFT_DIR = utils/libft

# Bibliotecas
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm -lXrandr -lXrender

# Busca todos os .c em subdiretórios de src/
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regra principal
all: $(NAME)

# Compilação do executável
$(NAME): $(LIBFT) $(MLX_DIR) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)
	@echo "✅ Compilado com sucesso: $(NAME)"

# Compila cada .c para .o no diretório obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compila a libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compila a minilibx
$(MLX_DIR):
	@$(MAKE) -C $(MLX_DIR)

# Limpeza de objetos
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objetos removidos"

# Limpeza total
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "🧹 Executável removido"

# Recompilação
re: fclean all

.PHONY: all clean fclean re
