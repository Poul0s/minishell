NAME	=	minishell
NAME_BONUS	=	minishell

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC		=	src/get/get_path.c \
			src/get/get_hostname.c \
			src/get/get_exec_name.c \
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
			src/parsing/utils.c \
			src/parsing/syntax_checker/token_generator.c \
			src/parsing/syntax_checker/syntax_char_checker.c \
			src/parsing/syntax_checker/syntax_checker.c \
			src/parsing/syntax_checker/print_syntax_error.c \
			src/parsing/insert_var_arg.c \
			src/parsing/parse_command_line.c \
			src/parsing/parse_command_group.c \
			src/parsing/parse_operator.c \
			src/parsing/parse_command.c \
			src/parsing/parse_argument.c \
			src/parsing/parse_file_redirection.c \
			src/cmd/ft_cd.c \
			src/cmd/ft_echo.c \
			src/cmd/ft_env.c \
			src/cmd/ft_pwd.c \
			src/cmd/export/print_env_sorted.c \
			src/cmd/export/export_multiple_env.c \
			src/cmd/export/ft_export.c \
			src/cmd/ft_unset.c \
			src/cmd/ft_exit.c \
			src/execution/execute_builtin.c \
			src/execution/execute_command_line.c \
			src/execution/get_path.c \
			src/execution/get_pid_res.c \
			src/execution/pipe.c \
			src/file/manage_file.c \
			src/file/clean_fd.c \
			src/file/here_doc/here_doc.c \
			src/file/here_doc/read_here_doc.c \
			src/file/here_doc/hd_create_data.c \
			src/file/here_doc/hd_generate_file.c \
			src/execution/execute_cmd.c \
			src/execution/variable_arguments/convert_variable_arguments.c \
			src/execution/variable_arguments/move_var_args.c \
			src/execution/variable_arguments/wildcard/wildcard.c \
			src/execution/variable_arguments/wildcard/get_next_wildcard.c \
			src/execution/variable_arguments/wildcard/insert_wildarguments.c \
			src/execution/variable_arguments/wildcard/sort_files.c \
			src/file/ls_dir.c \
			src/execution/find_close_cmd/find_close_cmd.c \
			src/execution/find_close_cmd/find_close_cmd_utils.c \
			src/signal/handler.c \
			src/free_utils.c \
			src/free_iofile.c \
			minishell.c \

SRC_BONUS		=	src_bonus/get/get_path_bonus.c \
					src_bonus/get/get_hostname_bonus.c \
					src_bonus/get/get_exec_name_bonus.c \
					src_bonus/get/refresh_prompt_prefix_bonus.c \
					src_bonus/autocompletion/find_match_bonus.c \
					src_bonus/autocompletion/wich_word_bonus.c \
					src_bonus/autocompletion/autocompletion_bonus.c \
					src_bonus/autocompletion/autocompletion_dir_bonus.c \
					src_bonus/autocompletion/is_first_bonus.c \
					src_bonus/environment_manager/del_env_var_bonus.c \
					src_bonus/environment_manager/edit_env_var_bonus.c \
					src_bonus/environment_manager/get_env_var_bonus.c \
					src_bonus/environment_manager/has_env_var_bonus.c \
					src_bonus/parsing/utils_bonus.c \
					src_bonus/parsing/syntax_checker/token_generator_bonus.c \
					src_bonus/parsing/syntax_checker/syntax_char_checker_bonus.c \
					src_bonus/parsing/syntax_checker/syntax_checker_bonus.c \
					src_bonus/parsing/syntax_checker/print_syntax_error_bonus.c \
					src_bonus/parsing/insert_var_arg_bonus.c \
					src_bonus/parsing/parse_command_line_bonus.c \
					src_bonus/parsing/parse_command_group_bonus.c \
					src_bonus/parsing/parse_operator_bonus.c \
					src_bonus/parsing/parse_command_bonus.c \
					src_bonus/parsing/parse_argument_bonus.c \
					src_bonus/parsing/parse_file_redirection_bonus.c \
					src_bonus/cmd/ft_cd_bonus.c \
					src_bonus/cmd/ft_echo_bonus.c \
					src_bonus/cmd/ft_env_bonus.c \
					src_bonus/cmd/ft_pwd_bonus.c \
					src_bonus/cmd/export/print_env_sorted_bonus.c \
					src_bonus/cmd/export/export_multiple_env_bonus.c \
					src_bonus/cmd/export/ft_export_bonus.c \
					src_bonus/cmd/ft_unset_bonus.c \
					src_bonus/cmd/ft_exit_bonus.c \
					src_bonus/execution/execute_builtin_bonus.c \
					src_bonus/execution/execute_command_line_bonus.c \
					src_bonus/execution/get_path_bonus.c \
					src_bonus/execution/get_pid_res_bonus.c \
					src_bonus/execution/pipe_bonus.c \
					src_bonus/file/manage_file_bonus.c \
					src_bonus/file/clean_fd_bonus.c \
					src_bonus/file/here_doc/here_doc_bonus.c \
					src_bonus/file/here_doc/read_here_doc_bonus.c \
					src_bonus/file/here_doc/hd_create_data_bonus.c \
					src_bonus/file/here_doc/hd_generate_file_bonus.c \
					src_bonus/execution/execute_cmd_bonus.c \
					src_bonus/execution/variable_arguments/convert_variable_arguments_bonus.c \
					src_bonus/execution/variable_arguments/move_var_args_bonus.c \
					src_bonus/execution/variable_arguments/wildcard/wildcard_bonus.c \
					src_bonus/execution/variable_arguments/wildcard/get_next_wildcard_bonus.c \
					src_bonus/execution/variable_arguments/wildcard/insert_wildarguments_bonus.c \
					src_bonus/execution/variable_arguments/wildcard/sort_files_bonus.c \
					src_bonus/file/ls_dir_bonus.c \
					src_bonus/execution/find_close_cmd/find_close_cmd_bonus.c \
					src_bonus/execution/find_close_cmd/find_close_cmd_utils_bonus.c \
					src_bonus/signal/handler_bonus.c \
					src_bonus/free_utils_bonus.c \
					src_bonus/free_iofile_bonus.c \
					minishell_bonus.c \

OBJ		=	$(addprefix obj/, $(SRC:.c=.o))
OBJ_BONUS		=	$(addprefix obj/, $(SRC_BONUS:.c=.o))

OBJ_DIR	=	$(sort $(dir $(OBJ)))

LFT_DIR	=	libft

LFT		=	$(LFT_DIR)/libft.a

LIBS	=	-lreadline -L$(LFT_DIR) -lft

HEADER	=	-I$(LFT_DIR)/header -Iinclude
HEADER_BONUS	=	-Iinclude_bonus


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

bonus: $(LFT) $(OBJ_DIR) $(OBJ_BONUS)
	@echo "$(GREEN)Linking $(NAME_BONUS)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) $(HEADER) $(HEADER_BONUS) -c $< -o $@

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
