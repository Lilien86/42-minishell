NAME = ./minishell

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc
CFLAGS = -g -Wextra -Werror -Wall -Wconversion -Wunreachable-code -Wunused-function -I $(LIBFT)
# Wconversion: Warns about implicit conversions
# Wunreachable-code: Warns about code that will never be executed
# Wunused-function: Warns if a static function is unused
LDFLAGS = -L $(LIBFT) -lft

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC = src/main.c src/parssing/tokenization.c src/parssing/tokenization_utils.c 

OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIBRARY):
	/bin/make --quiet -C $(LIBFT)

$(NAME): $(LIBFT_LIBRARY) $(OBJ)
	@echo
	@echo "$(YELLOW)Compiling source files...$(NC)"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation is complete. Generated executable: $(NAME).$(NC)"
	@echo

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@echo
	@echo "$(YELLOW)Compiling file $<...$(NC)"
	@$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)
	@echo

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

clean:
	@echo
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@/bin/make --quiet -C $(LIBFT) clean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaning complete.$(NC)"
	@echo

fclean: clean
	@echo
	@echo "$(YELLOW)Removing executable $(NAME)...$(NC)"
	@/bin/make --quiet -C $(LIBFT) fclean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Removal complete.$(NC)"
	@echo

re: fclean all

.PHONY: all clean fclean re
