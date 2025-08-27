# ===========================================
# Makefile para projeto ray-trace (Linux/WSL)
# ===========================================

# Compilador e flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I../include
RM      = rm -f

# Diretórios
TEST_DIR       = .
TUPLE_TESTS    = $(TEST_DIR)/tuple
VECTOR_TESTS   = $(TEST_DIR)/vector
RGB_TESTS      = $(TEST_DIR)/rgb
CANVAS_TESTS   = $(TEST_DIR)/canvas
MATRIX_TESTS   = $(TEST_DIR)/matrix
TRANSF_TESTS   = $(TEST_DIR)/transformation
RAY_DIR        = $(TEST_DIR)/ray
SPHERE_TESTS   = $(TEST_DIR)/sphere
HIT_TESTS      = $(TEST_DIR)/intersections
NORMAL_TESTS   = $(TEST_DIR)/normal
REFLECT_TESTS  = $(TEST_DIR)/reflect
LIGHT_TESTS    = $(TEST_DIR)/light
LIGHTING_TESTS = $(TEST_DIR)/lighting
MATERIAL_TESTS = $(TEST_DIR)/material
WORLD_TESTS    = $(TEST_DIR)/world
COMPUTATION_TESTS = $(TEST_DIR)/computation

LIBFT_DIR     = ../utils/libft
CORE_DIR      = ../src
MINILIBX_DIR  = ../includes/minilibx-linux

# Nome do executável de testes
TEST_BIN = test_runner

# Bibliotecas
LIBFT    = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx.a

# Arquivos de fontes para os testes
TEST_SRCS = $(TEST_DIR)/test_utils.c \
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
            $(RGB_TESTS)/color_at_test.c \
            $(CANVAS_TESTS)/canvas_tests.c \
            $(MATRIX_TESTS)/matrix_tests.c \
            $(MATRIX_TESTS)/matrix_multiply_by_matrix_tests.c \
            $(MATRIX_TESTS)/matrix_multiply_by_tuple_tests.c \
            $(MATRIX_TESTS)/identity_matrix_tests.c \
            $(MATRIX_TESTS)/rotate_matrix_tests.c \
            $(MATRIX_TESTS)/determinant_matrix_tests.c \
            $(MATRIX_TESTS)/submatrix_tests.c \
            $(MATRIX_TESTS)/minor_matrix_test.c \
            $(MATRIX_TESTS)/cofactor_matrix_test.c \
			$(MATRIX_TESTS)/invertible_matrix_test.c \
            $(TRANSF_TESTS)/translation_point_test.c \
            $(TRANSF_TESTS)/translation_vector_test.c \
            $(TRANSF_TESTS)/transformation_tests.c \
            $(TRANSF_TESTS)/scaling_tests.c \
            $(TRANSF_TESTS)/rotation_tests.c \
            $(TRANSF_TESTS)/shearing_tests.c \
            $(TRANSF_TESTS)/test_chained_transformations.c \
            $(RAY_DIR)/ray_tests.c \
            $(RAY_DIR)/ray_transform_tests.c \
            $(SPHERE_TESTS)/sphere_tests.c \
            $(SPHERE_TESTS)/sphere_transform_tests.c \
            $(HIT_TESTS)/hit_tests.c \
            $(NORMAL_TESTS)/normal_test.c \
            $(REFLECT_TESTS)/reflect_test.c \
            $(LIGHT_TESTS)/light_test.c \
            $(MATERIAL_TESTS)/material_test.c \
            $(LIGHTING_TESTS)/lighting_test.c \
            $(WORLD_TESTS)/world_test.c \
            $(COMPUTATION_TESTS)/computation_test.c \
            $(HIT_TESTS)/shade_hit_test.c \
            $(TEST_DIR)/tests.c \

CORE_SRCS = $(CORE_DIR)/tuple/tuple.c \
            $(CORE_DIR)/tuple/tuple_utils.c \
            $(CORE_DIR)/tuple/vector.c \
            $(CORE_DIR)/rgb/rgb.c \
            $(CORE_DIR)/rgb/rgb_utils.c \
            $(CORE_DIR)/canvas/canvas.c \
            $(CORE_DIR)/matrix/matrix.c \
            $(CORE_DIR)/matrix/matrix_utils.c \
            $(CORE_DIR)/matrix/matrix_multiply.c \
            $(CORE_DIR)/matrix/matrix_rotate.c \
            $(CORE_DIR)/matrix/minor_matrix.c \
            $(CORE_DIR)/matrix/cofactor_matrix.c \
            $(CORE_DIR)/matrix/matrix_determinant.c \
			$(CORE_DIR)/matrix/matrix_invertible.c \
            $(CORE_DIR)/mlx_adapter/open_mlx_screen.c \
            $(CORE_DIR)/mlx_adapter/canvas_to_mlx_image.c \
            $(CORE_DIR)/transformation/translation.c \
            $(CORE_DIR)/transformation/scaling.c \
            $(CORE_DIR)/transformation/rotation.c \
            $(CORE_DIR)/transformation/shearing.c \
            $(CORE_DIR)/ray/ray.c \
            $(CORE_DIR)/ray/ray_utils.c \
            $(CORE_DIR)/sphere/sphere.c \
            $(CORE_DIR)/intersection/intersection.c \
            $(CORE_DIR)/intersection/hit.c \
            $(CORE_DIR)/intersection/intersection_list.c \
            $(CORE_DIR)/objects/object.c \
            $(CORE_DIR)/normal/normal.c \
            $(CORE_DIR)/reflect/reflect.c \
            $(CORE_DIR)/light/light.c \
            $(CORE_DIR)/light/lighting.c \
            $(CORE_DIR)/material/material.c \
            $(CORE_DIR)/world/world.c \
            $(CORE_DIR)/world/shade.c \
            $(CORE_DIR)/computation/prepare_computation.c \
            $(CORE_DIR)/utils/solve_quadratic.c

TEST_SRCS += $(CORE_SRCS)

# Arquivos de objeto
TEST_OBJS = $(TEST_SRCS:.c=.o)

# ===========================================
# Regras
# ===========================================

# Compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Criar objeto para arquivos do core no mesmo nível (incluindo intersect_world.c)
$(CORE_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar o test_runner
$(TEST_BIN): $(TEST_OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MINILIBX_DIR)
	$(CC) $(TEST_OBJS) $(LIBFT) $(MINILIBX) -o $(TEST_BIN) -I$(MINILIBX_DIR) -lXext -lX11 -lreadline -lm
	@printf "\e[92;5;118m- Test runner ready.\n\e[0m"

# Compilar tudo
all: $(TEST_BIN)

# Rodar testes
run: $(TEST_BIN)
	./$(TEST_BIN)

# Rodar com valgrind
leaks: $(TEST_BIN)
	@valgrind --leak-check=full --error-exitcode=1 ./$(TEST_BIN) 2>&1 | tee valgrind_output.log | grep -E "definitely lost|indirectly lost" > /dev/null && \
	(echo "\e[91m❌ Memory leaks detected! Check log:\e[0m"; cat valgrind_output.log) || \
	(echo "\e[92m✅ No memory leaks detected!\e[0m")
	@rm -f valgrind_output.log

# Limpeza de objetos
clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(TEST_OBJS)
	@printf "\e[93;5;226m- Test objects removed.\n\e[0m"

# Limpeza completa
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(TEST_BIN)
	@printf "\e[93;5;226m- Test runner removed.\n\e[0m"

# Recompilar tudo
re: fclean all

.PHONY: all clean fclean re run leaks
