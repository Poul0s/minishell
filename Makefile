CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC		=	src/get/get_path.c \
			src/get/get_hostname.c \
			src/get/refresh_prompt_prefix.c \
			src/autocompletion/find_match.c \
			src/autocompletion/wich_word.c \
			src/autocompletion/autocompletion.c \
			src/autocompletion/autocompletion_dir.c \
			src/autocompletion/is_first.c \
			src/environment_manager/del_env_var.c \
			src/environment_manager/edit_env_var.c \
			src/environment_manager/get_env_var.c \
			src/environment_manager/has_env_var.c \
			src/parsing/skip_spaces.c \
			src/parsing/syntax_checker/token_generator.c \
			src/parsing/syntax_checker/syntax_checker.c \
			src/parsing/insert_variable_argument.c \
			src/parsing/parse_command_line.c \
			src/parsing/parse_command_group.c \
			src/parsing/parse_command.c \
			src/parsing/parse_argument.c \
			src/parsing/parse_file_redirection.c \
			src/cmd/ft_cd.c \
			src/cmd/ft_echo.c \
			src/cmd/ft_env.c \
			src/cmd/ft_pwd.c \
			src/cmd/ft_export.c \
			src/execution/execute_builtin.c \
			src/execution/execute_cache.c \
			src/execution/execute_command_line.c \
			src/execution/get_path.c \
			src/execution/pipe.c \
			src/execution/execute_cmd.c \
			src/execution/find_close_cmd.c \
			src/signal/handler.c \
			src/free_command_line.c \
			minishell.c \

OBJ		=	$(addprefix obj/, $(SRC:.c=.o))

OBJ_DIR	=	$(sort $(dir $(OBJ)))

LFT_DIR	=	libft

LFT		=	$(LFT_DIR)/libft.a

LIBS	=	-lreadline -L$(LFT_DIR) -lft

HEADER	=	-I$(LFT_DIR)/header -Iinclude

NAME	=	minishell

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPULE = \e[0;35m
NC = \033[0m

all: $(NAME)

# LIBS

$(LFT):
	@echo "$(PURPULE)Building libft...$(NC)"
	@make -C $(LFT_DIR) -s -j

# COMMANDS

$(NAME): $(LFT) $(OBJ_DIR) $(OBJ)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

obj/%.o: %.c
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) $(HEADER) $^ -o $@ -c

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf obj/

lclean:
	@echo "$(RED)Cleaning libft...$(NC)"
	@make -C $(LFT_DIR) fclean -s -j

fclean: clean lclean
	@echo "$(RED)Cleaning executable $(NAME)...$(NC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
