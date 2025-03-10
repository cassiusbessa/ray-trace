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
MATRIX_TESTS = $(TEST_DIR)/matrix
LIBFT_DIR   = ../utils/libft
CORE_DIR	= ../src
MINILIBX_DIR = ../minilibx-linux

# Nome do executável de testes
TEST_BIN    = test_runner

# Biblioteca auxiliar
LIBFT       = $(LIBFT_DIR)/libft.a
MINILIBX    = $(MINILIBX_DIR)/libmlx.a

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
				$(CANVAS_TESTS)/canvas_tests.c \
				$(MATRIX_TESTS)/matrix_tests.c \
				$(MATRIX_TESTS)/matrix_multiply_by_matrix_tests.c \
				$(MATRIX_TESTS)/matrix_multiply_by_tuple_tests.c \
				$(MATRIX_TESTS)/identity_matrix_tests.c \
				$(MATRIX_TESTS)/rotate_matrix_tests.c \
				$(MATRIX_TESTS)/determinant_matrix_tests.c \
				$(MATRIX_TESTS)/submatrix_tests.c \
				$(MATRIX_TESTS)/matrix_minor_cofator_tests.c \
				$(MATRIX_TESTS)/matrix_invert_tests.c \
				$(MATRIX_TESTS)/matrix_inverse_tests.c \
				$(TEST_DIR)/tests.c

CORE_SRCS	=	$(CORE_DIR)/tuple/tuple.c \
				$(CORE_DIR)/tuple/tuple_utils.c \
				$(CORE_DIR)/tuple/vector.c \
				$(CORE_DIR)/rgb/rgb.c \
				$(CORE_DIR)/rgb/rgb_utils.c \
				$(CORE_DIR)/canvas/canvas.c \
				$(CORE_DIR)/matrix/matrix.c \
				$(CORE_DIR)/matrix/matrix_utils.c \
				$(CORE_DIR)/matrix/matrix_multiply.c \
				$(CORE_DIR)/matrix/matrix_rotate.c \
				$(CORE_DIR)/matrix/matrix_inverse.c \
				$(CORE_DIR)/mlx_adapter/open_mlx_screen.c \
				$(CORE_DIR)/mlx_adapter/canvas_to_mlx_image.c


TEST_SRCS	+= $(CORE_SRCS)

# Arquivos de objeto
TEST_OBJS   = $(TEST_SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar os testes
$(TEST_BIN): $(TEST_OBJS)
	@make -C $(LIBFT_DIR)
	@make -C ../minilibx-linux
	$(CC) $(TEST_OBJS) $(LIBFT) $(MINILIBX) -o $(TEST_BIN) -Imlx_linux -lXext -lX11 -lreadline -lm
	@printf "\e[92;5;118m    - Test runner ready.\n\e[0m"

all: $(TEST_BIN)

run: $(TEST_BIN)
	./$(TEST_BIN)

leaks: $(TEST_BIN)
	@valgrind --leak-check=full --error-exitcode=1 ./$(TEST_BIN) 2>&1 | tee valgrind_output.log | grep -E "definitely lost|indirectly lost" > /dev/null && \
		(echo "\e[91m❌ Memory leaks detected! Check the log below:\e[0m"; cat valgrind_output.log) || \
		(echo "\e[92m✅ No memory leaks detected!\e[0m")
	@rm -f valgrind_output.log



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
