CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC		=	src/get/get_path.c \
			src/get/get_hostname.c \
			src/get/refresh_prompt_prefix.c \
			src/autocompletion/find_match.c \
			src/autocompletion/wich_word.c \
			src/autocompletion/autocompletion.c \
			src/autocompletion/autocompletion_dir.c \
			src/cmd/ft_pwd.c \
			src/parsing/parse_command_line.c \
			src/parsing/parse_commands.c \
			src/parsing/parse_command.c \
			src/parsing/parse_argument.c \
			src/parsing/parse_file_redirection.c \
			debug.c \
			src/signal/handler.c \
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
