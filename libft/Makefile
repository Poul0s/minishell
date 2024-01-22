# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 11:02:12 by psalame           #+#    #+#              #
#    Updated: 2024/01/22 16:56:07 by psalame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	libft.a

SRCS		=	ft_string/ft_strlen.c \
				ft_string/ft_strlcpy.c \
				ft_string/ft_strlcat.c \
				ft_string/ft_strchr.c \
				ft_string/ft_strrchr.c \
				ft_string/ft_strdup.c \
				ft_string/ft_strnstr.c \
				ft_string/ft_strncmp.c \
				ft_string/ft_split.c \
				ft_string/ft_striteri.c \
				ft_string/ft_strjoin.c \
				ft_string/ft_strmapi.c \
				ft_string/ft_strtrim.c \
				ft_string/ft_substr.c \
				ft_string/ft_strs.c \
				ft_string/ft_str_insert.c \
				\
				ft_is/ft_isalpha.c \
				ft_is/ft_isdigit.c \
				ft_is/ft_isalnum.c \
				ft_is/ft_isascii.c \
				ft_is/ft_isprint.c \
				\
				ft_memoryManager/ft_memset.c \
				ft_memoryManager/ft_memcmp.c \
				ft_memoryManager/ft_memchr.c \
				ft_memoryManager/ft_memmove.c \
				ft_memoryManager/ft_memcpy.c \
				ft_memoryManager/ft_bzero.c \
				ft_memoryManager/ft_calloc.c \
				\
				ft_convert/ft_tolower.c \
				ft_convert/ft_toupper.c \
				ft_convert/ft_atoi.c \
				ft_convert/ft_itoa.c \
				ft_convert/ft_ultoa_base.c \
				ft_convert/ft_abs.c \
				\
				ft_print/ft_putstr_fd.c \
				ft_print/ft_putchar_fd.c \
				ft_print/ft_putchar_rep.c \
				ft_print/ft_putendl_fd.c \
				ft_print/ft_putnbr_fd.c \
				ft_print/ft_putptr_fd.c \
				ft_print/ft_putunbr_fd.c \
				ft_print/ft_putxnbr_fd.c \
				ft_print/printf/ft_printf.c \
				ft_print/printf/utils/combinaison_flag.c \
				ft_print/printf/utils/conversion_flag.c \
				ft_print/printf/utils/print_functions/ft_printf_char.c \
				ft_print/printf/utils/print_functions/ft_printf_hexa.c \
				ft_print/printf/utils/print_functions/ft_printf_int.c \
				ft_print/printf/utils/print_functions/ft_printf_ptr.c \
				ft_print/printf/utils/print_functions/ft_printf_string.c \
				ft_print/printf/utils/print_functions/ft_printf_uint.c \
				\
				ft_linkedList/ft_lstnew.c \
				ft_linkedList/ft_lstsize.c \
				ft_linkedList/ft_lstlast.c \
				ft_linkedList/ft_lstadd_front.c \
				ft_linkedList/ft_lstadd_back.c \
				ft_linkedList/ft_lstdelone.c \
				ft_linkedList/ft_lstclear.c \
				ft_linkedList/ft_lstiter.c \
				ft_linkedList/ft_lstmap.c \
				ft_linkedList/ft_lstremoveif.c \
				\
				ft_parse/ft_read_to_cstr.c \
				ft_parse/get_next_line.c

OBJS		=	$(addprefix obj/, $(SRCS:.c=.o))

OBJS_DIRS	=	$(sort $(dir $(OBJS)))

HEADER		=	header

all: $(NAME)

$(NAME): $(OBJS_DIRS) $(OBJS) 
	ar -rc $@ $(OBJS)

$(OBJS_DIRS):
	@mkdir -p $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -I $(HEADER) -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
