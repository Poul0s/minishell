CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	src/ft_pwd.c \
			src/get_hostname.c \
			src/refresh_prompt_prefix.c \
			minishell.c \

OBJ		=	$(addprefix obj/, $(SRC:.c=.o))

OBJ_DIR	=	$(sort $(dir $(OBJ)))

LFT_DIR	=	libft

LFT		=	$(LFT_DIR)/libft.a

LIBS	=	-lreadline -L$(LFT_DIR) -lft

HEADER	=	-I$(LFT_DIR)/header -Iinclude

NAME	=	minishell

all: $(NAME)

# LIBS

$(LFT):
	@echo "Building libraries..."
	@make -C $(LFT_DIR) -s

# COMMANDS

$(NAME): $(LFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

obj/%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) $^ -o $@ -c

$(OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf obj/

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
