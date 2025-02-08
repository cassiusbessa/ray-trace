# Cores para saída do terminal
GREEN       = \e[92;5;118m
YELLOW      = \e[93;5;226m
GRAY        = \e[33;2;37m
RESET       = \e[0m
CURSIVE     = \e[33;3m

# Definição de variáveis
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Caminhos
TUPLE_DIR   = src/tuple
TEST_DIR    = tests
INCLUDE_DIR = include
LIBFT_DIR   = utils/libft

# Nome do executável
MINIRT      = miniRT
TEST_BIN    = test_runner

# Biblioteca auxiliar
LIBFT       = $(LIBFT_DIR)/libft.a

# Arquivos de fontes (explicitamente definidos)
SRCS        = $(TUPLE_DIR)/tuple.c

TEST_SRCS	=	$(TEST_DIR)/test_utils.c \
				$(TEST_DIR)/tuple_tests.c \
				$(TEST_DIR)/tuple_op_tests.c \
				$(TEST_DIR)/main_tests.c

# Arquivos de objeto
OBJS         = $(SRCS:.c=.o)
TEST_OBJS    = $(TEST_SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
$(TUPLE_DIR)/%.o: $(TUPLE_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
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
