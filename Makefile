# Cores para saída do terminal
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

# Definição de variáveis
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

# Caminhos
SRC_DIR		= src
ENTITIES_DIR = src/entities
TEST_DIR	= tests
INCLUDE_DIR = include
LIBFT_DIR	= utils/libft

# Nome do executável
MINIRT	= miniRT
TEST_BIN = test_runner

# Biblioteca auxiliar
LIBFT	= $(LIBFT_DIR)/libft.a

# Coletar os arquivos-fonte automaticamente
SRCS	= $(wildcard $(SRC_DIR)/*.c) \
          $(wildcard $(ENTITIES_DIR)/*.c)

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

OBJS	= $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar o miniRT
$(MINIRT): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBFT) -o $(MINIRT) -lreadline
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

all: $(MINIRT)

# Compilar os testes
$(TEST_BIN): $(TEST_OBJS) $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(TEST_OBJS) $(OBJS) $(LIBFT) -o $(TEST_BIN)
	@printf "$(GREEN)    - Test runner ready.\n$(RESET)"

test: $(TEST_BIN)
	./$(TEST_BIN)

# Limpeza
clean:
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(TEST_OBJS)
	@printf "$(YELLOW)    - Objects removed.$(RESET)\n"

fclean: clean
	$(RM) $(MINIRT) $(TEST_BIN)
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re test
