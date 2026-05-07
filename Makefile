#cores
BG_GREEN = \033[42m
WHITE = \033[97m
BLACK = \033[30m
CINZA = \033[47m\033[30m
GREEN = \033[32m
RESET = \033[0m

#flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I. -Iincludes
EXEC = pipex
OBJ_DIR = Obj

#src_arquives
SRCS_DIR = src
SRC_PRINTF = ft_printf_error/ft_putchar_error.c ft_printf_error/ft_putstr_error.c \
	ft_printf_error/ft_putnbr_error.c ft_printf_error/ft_putnbr_hexa_error.c \
	ft_printf_error/ft_add_error.c ft_printf_error/ft_printf_error.c
SRC_LIBFT = libft/ft_split.c libft/ft_strchr.c libft/ft_strjoin.c \
	libft/ft_strlen.c libft/ft_free_double_pointer.c

SRC = $(SRC_LIBFT) $(SRC_PRINTF) error.c ft_env_line.c pipex.c utils.c
SRC := $(addprefix $(SRCS_DIR)/, $(SRC))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(EXEC)

$(EXEC): $(OBJ) $(MLX_ARQ)
		@echo "$(BG_GREEN)$(BLACK)[CREATE] P... PI... PIP... PIPE... PIPEX *-* $(EXEC)$(RESET)"
		@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/$(SRCS_DIR)/libft/%.o: $(SRCS_DIR)/libft/%.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(SRCS_DIR)/ft_printf_error/%.o: $(SRCS_DIR)/ft_printf_error/%.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@echo "$(GREEN)[COMPILE] $<$(RESET)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(MLX_ARQ):
		@cd $(dir $@) && make

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		@echo " 🗑️  Andou, andou e no lixo parouu!"
		@rm -f $(EXEC)

git:
	@git add .
	@git commit -m "$(m)"
	@git push

norma:
		@norminette .

re: fclean all

.PHONY: re fclean clean all
