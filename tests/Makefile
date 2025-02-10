# Definição de variáveis
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I../include
RM          = rm -f

# Caminhos
TEST_DIR    = .
TUPLE_TESTS = $(TEST_DIR)/tuple
VECTOR_TESTS = $(TEST_DIR)/vector
RGB_TESTS = $(TEST_DIR)/rgb
CANVAS_TESTS = $(TEST_DIR)/canvas
LIBFT_DIR   = ../utils/libft
CORE_DIR	= ../src

# Nome do executável de testes
TEST_BIN    = test_runner

# Biblioteca auxiliar
LIBFT       = $(LIBFT_DIR)/libft.a

# Arquivos de fontes para testes
TEST_SRCS	=	$(TEST_DIR)/test_utils.c \
				$(TUPLE_TESTS)/tuple_common_tests.c \
				$(TUPLE_TESTS)/tuple_tests.c \
				$(TUPLE_TESTS)/tuple_op_tests.c \
				$(TUPLE_TESTS)/tuple_multiply_tests.c \
				$(VECTOR_TESTS)/vector_magnitude_tests.c \
				$(VECTOR_TESTS)/vector_normalize_tests.c \
				$(VECTOR_TESTS)/vector_dot_product_tests.c \
				$(VECTOR_TESTS)/vector_cross_product_test.c \
				$(VECTOR_TESTS)/vector_tests.c \
				$(RGB_TESTS)/rgb_tests.c \
				$(RGB_TESTS)/rgb_common_tests.c \
				$(TEST_DIR)/tests.c

CORE_SRCS	=	$(CORE_DIR)/tuple/tuple.c \
				$(CORE_DIR)/tuple/tuple_utils.c \
				$(CORE_DIR)/tuple/vector.c \
				$(CORE_DIR)/rgb/rgb.c \
				$(CORE_DIR)/rgb/rgb_utils.c \
				$(CORE_DIR)/canvas/canvas.c


TEST_SRCS	+= $(CORE_SRCS)

# Arquivos de objeto
TEST_OBJS   = $(TEST_SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar os testes
$(TEST_BIN): $(TEST_OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(TEST_OBJS) $(LIBFT) -o $(TEST_BIN) -lm
	@printf "\e[92;5;118m    - Test runner ready.\n\e[0m"

all: $(TEST_BIN)

run: $(TEST_BIN)
	./$(TEST_BIN)

# Limpeza
clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(TEST_OBJS)
	@printf "\e[93;5;226m    - Test objects removed.\n\e[0m"

fclean: clean
	$(RM) $(TEST_BIN)
	@printf "\e[93;5;226m    - Test runner removed.\n\e[0m"

re: fclean all

.PHONY: all clean fclean re run
