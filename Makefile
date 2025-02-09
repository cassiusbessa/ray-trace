# Definição de variáveis
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Caminhos
TUPLE_DIR   = src/tuple
VECTOR_DIR  = src/vector
INCLUDE_DIR = include
LIBFT_DIR   = utils/libft
TESTS_DIR   = tests

# Nome do executável
MINIRT      = miniRT

# Biblioteca auxiliar
LIBFT       = $(LIBFT_DIR)/libft.a

# Arquivos de fontes do miniRT
SRCS        = $(TUPLE_DIR)/tuple.c \
              $(TUPLE_DIR)/tuple_utils.c \
			  $(TUPLE_DIR)/vector.c \
			  src/thick.c

# Arquivos de objeto
OBJS         = $(SRCS:.c=.o)

# Regra padrão para compilação de .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compilar o miniRT
$(MINIRT): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBFT) -o $(MINIRT) -lreadline -lm
	@printf "\e[92;5;118m    - Executable ready.\n\e[0m"

all: $(MINIRT)

# Chamar Makefile de testes
test:
	@$(MAKE) -C $(TESTS_DIR) run

# Limpeza
clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(TESTS_DIR)
	$(RM) $(OBJS)
	@printf "\e[93;5;226m    - Objects removed.\n\e[0m"

fclean: clean
	@make fclean -C $(TESTS_DIR)
	$(RM) $(MINIRT)
	@printf "\e[93;5;226m    - Executable removed.\n\e[0m"

re: fclean all

.PHONY: all clean fclean re test
