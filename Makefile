CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC		=	src/get_path.c \
			src/get_hostname.c \
			src/refresh_prompt_prefix.c \
			src/find_match_cmd.c \
			src/cmd/ft_pwd.c \
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
