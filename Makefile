# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 13:34:07 by almighty          #+#    #+#              #
#    Updated: 2026/01/19 09:26:59 by tpanou-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS  := -Wall -Wextra -Werror -g

DIR_SRCS	:= srcs
DIR_OBJS	:= objs
DIR_SRCS_BON	:= srcs/bonus
DIR_OBJS_BON	:= objs/bonus
SRCS	:=	$(DIR_SRCS)/main/create_error.c\
			$(DIR_SRCS)/main/main.c\
			$(DIR_SRCS)/main/raboushell.c\
			$(DIR_SRCS)/main/get_prompt.c\
			$(DIR_SRCS)/main/exit_raboushell.c\
			$(DIR_SRCS)/main/throw_error.c\
			$(DIR_SRCS)/main/utils.c\
			$(DIR_SRCS)/main/memory.c\
			$(DIR_SRCS)/main/signal.c\
			$(DIR_SRCS)/main/utils2.c\
			$(DIR_SRCS)/parsing/check_shell_parsing.c\
			$(DIR_SRCS)/parsing/expand_utils.c\
			$(DIR_SRCS)/parsing/expand.c\
			$(DIR_SRCS)/parsing/get_arg.c\
			$(DIR_SRCS)/parsing/get_argv_redirv.c\
			$(DIR_SRCS)/parsing/get_shell_line.c\
			$(DIR_SRCS)/parsing/get_cmd.c\
			$(DIR_SRCS)/parsing/get_hdoc.c\
			$(DIR_SRCS)/parsing/get_redir_name_len.c\
			$(DIR_SRCS)/parsing/get_redir.c\
			$(DIR_SRCS)/parsing/go_to_end_of.c\
			$(DIR_SRCS)/parsing/memory.c\
			$(DIR_SRCS)/parsing/parsing_utils.c\
			$(DIR_SRCS)/parsing/parsing_utils2.c\
			$(DIR_SRCS)/parsing/parsing_utils3.c\
			$(DIR_SRCS)/parsing/parsing_utils4.c\
			$(DIR_SRCS)/exec/exec_shell_op_line.c\
			$(DIR_SRCS)/exec/exec_cmd.c\
			$(DIR_SRCS)/exec/get_path.c\
			$(DIR_SRCS)/exec/pipes.c\
			$(DIR_SRCS)/exec/redirs.c\
			$(DIR_SRCS)/exec/exec_utils.c\
			$(DIR_SRCS)/exec/exec_utils2.c\
			$(DIR_SRCS)/builtins/builtin_cd.c\
			$(DIR_SRCS)/builtins/builtin_echo.c\
			$(DIR_SRCS)/builtins/builtin_env.c\
			$(DIR_SRCS)/builtins/builtin_export.c\
			$(DIR_SRCS)/builtins/builtin_exit.c\
			$(DIR_SRCS)/builtins/builtin_pwd.c\
			$(DIR_SRCS)/builtins/builtin_unset.c\
			$(DIR_SRCS)/builtins/util_convert_export_to_var.c\
			$(DIR_SRCS)/builtins/util_envp.c\
			$(DIR_SRCS)/builtins/util_exportp.c\
			$(DIR_SRCS)/builtins/util_find_var.c\
			$(DIR_SRCS)/builtins/util_safe_getcwd.c\
			$(DIR_SRCS)/builtins/util_throw_builtin_error.c\
			$(DIR_SRCS)/get_line/end_get_line.c\
			$(DIR_SRCS)/get_line/get_line_utils.c\
			$(DIR_SRCS)/get_line/get_line.c\
			$(DIR_SRCS)/get_line/handle_ctrl.c\
			$(DIR_SRCS)/get_line/handle_keys.c\
			$(DIR_SRCS)/get_line/history_utils.c\
			$(DIR_SRCS)/get_line/history.c\
			$(DIR_SRCS)/get_line/line_editing.c\
			$(DIR_SRCS)/get_line/memory.c\
			$(DIR_SRCS)/get_line/move_cursor.c\
			$(DIR_SRCS)/get_line/rewrite_line.c\

SRCS_BON	:=	$(DIR_SRCS_BON)/main/create_error_bonus.c\
				$(DIR_SRCS_BON)/main/main_bonus.c\
				$(DIR_SRCS_BON)/main/raboushell_bonus.c\
				$(DIR_SRCS_BON)/main/get_prompt_bonus.c\
				$(DIR_SRCS_BON)/main/exit_raboushell_bonus.c\
				$(DIR_SRCS_BON)/main/throw_error_bonus.c\
				$(DIR_SRCS_BON)/main/utils_bonus.c\
				$(DIR_SRCS_BON)/main/memory_bonus.c\
				$(DIR_SRCS_BON)/main/signal_bonus.c\
				$(DIR_SRCS_BON)/main/utils2_bonus.c\
				$(DIR_SRCS_BON)/parsing/check_shell_parsing_bonus.c\
				$(DIR_SRCS_BON)/parsing/expand_utils_bonus.c\
				$(DIR_SRCS_BON)/parsing/expand_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_arg_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_argv_redirv_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_shell_line_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_cmd_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_hdoc_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_redir_name_len_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_redir_bonus.c\
				$(DIR_SRCS_BON)/parsing/go_to_end_of_bonus.c\
				$(DIR_SRCS_BON)/parsing/memory_bonus.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils_bonus.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils2_bonus.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils3_bonus.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils4_bonus.c\
				$(DIR_SRCS_BON)/exec/exec_shell_op_line_bonus.c\
				$(DIR_SRCS_BON)/exec/exec_cmd_bonus.c\
				$(DIR_SRCS_BON)/exec/get_path_bonus.c\
				$(DIR_SRCS_BON)/exec/pipes_bonus.c\
				$(DIR_SRCS_BON)/exec/redirs_bonus.c\
				$(DIR_SRCS_BON)/exec/exec_utils_bonus.c\
				$(DIR_SRCS_BON)/exec/exec_utils2_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_cd_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_echo_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_env_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_export_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_exit_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_pwd_bonus.c\
				$(DIR_SRCS_BON)/builtins/builtin_unset_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_convert_export_to_var_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_envp_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_exportp_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_find_var_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_safe_getcwd_bonus.c\
				$(DIR_SRCS_BON)/builtins/util_throw_builtin_error_bonus.c\
				$(DIR_SRCS_BON)/get_line/end_get_line_bonus.c\
				$(DIR_SRCS_BON)/get_line/get_line_utils_bonus.c\
				$(DIR_SRCS_BON)/get_line/get_line_bonus.c\
				$(DIR_SRCS_BON)/get_line/handle_ctrl_bonus.c\
				$(DIR_SRCS_BON)/get_line/handle_keys_bonus.c\
				$(DIR_SRCS_BON)/get_line/history_utils_bonus.c\
				$(DIR_SRCS_BON)/get_line/history_bonus.c\
				$(DIR_SRCS_BON)/get_line/line_editing_bonus.c\
				$(DIR_SRCS_BON)/get_line/memory_bonus.c\
				$(DIR_SRCS_BON)/get_line/move_cursor_bonus.c\
				$(DIR_SRCS_BON)/get_line/rewrite_line_bonus.c\

OBJS	:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))
OBJS_BON	:=	$(patsubst %.c, $(DIR_OBJS_BON)/%.o,\
				 $(subst $(DIR_SRCS_BON)/,,$(SRCS_BON)))

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@curr=$$(find objs -iname "*.o" | wc -l); \
	total=$$(find srcs -iname *.c -not -iname .*.c | wc -l); \
	printf "\r\e[?25lCompiling : \e[1m⟬\e[107m%*s\e[0m%*s\e[1m⟭\e[0m %d/%d" \
		$$curr "" $$(($$total - $$curr)) "" $$curr $$total

$(DIR_OBJS_BON)/%.o: $(DIR_SRCS_BON)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@curr=$$(find objs -iname "*.o" | wc -l); \
	total=$$(find srcs -iname *.c -not -iname .*.c | wc -l); \
	printf "\r\e[?25lCompiling : \e[1m⟬\e[107m%*s\e[0m%*s\e[1m⟭\e[0m %d/%d" \
		$$curr "" $$(($$total - $$curr)) "" $$curr $$total

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

all : $(NAME)

bonus : $(OBJS_BON)
	@$(CC) $(CFLAGS) $(OBJS_BON) -o $(NAME)
	@printf "\n✅ Compilation completed: $(NAME)\e[?25h\n"

clean :
	@rm -rf $(DIR_OBJS)
	@rm -rf $(DIR_OBJS_BON)
	@echo "✅ clean done."

fclean : clean
	@rm -f $(NAME)
	@echo "✅ fclean done."

re : fclean all

.PHONY : all bonus clean fclean re