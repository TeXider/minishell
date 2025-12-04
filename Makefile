# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almighty <almighty@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/02 13:34:07 by almighty          #+#    #+#              #
#    Updated: 2025/12/04 10:32:04 by almighty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS  := -Wall -Wextra -Werror -g


DIR_SRCS	:= srcs
DIR_OBJS	:= objs

SRCS	:=	$(DIR_SRCS)/main/create_error.c\
			$(DIR_SRCS)/main/main.c\
			$(DIR_SRCS)/main/raboushell.c\
			$(DIR_SRCS)/main/exit_raboushell.c\
			$(DIR_SRCS)/main/throw_error.c\
			$(DIR_SRCS)/main/utils.c\
			$(DIR_SRCS)/main/memory.c\
			$(DIR_SRCS)/main/signal.c\
			$(DIR_SRCS)/main/utils2.c\
			$(DIR_SRCS)/parsing/cmd_funcs.c\
			$(DIR_SRCS)/parsing/expand_utils.c\
			$(DIR_SRCS)/parsing/expand.c\
			$(DIR_SRCS)/parsing/get_arg.c\
			$(DIR_SRCS)/parsing/get_argv_redirv.c\
			$(DIR_SRCS)/parsing/get_cmd_line.c\
			$(DIR_SRCS)/parsing/get_hdoc.c\
			$(DIR_SRCS)/parsing/get_redir_name_len.c\
			$(DIR_SRCS)/parsing/get_redir.c\
			$(DIR_SRCS)/parsing/go_to_end_of.c\
			$(DIR_SRCS)/parsing/parsing_utils.c\
			$(DIR_SRCS)/parsing/parsing_utils2.c\
			$(DIR_SRCS)/parsing/parsing_utils3.c\
			$(DIR_SRCS)/exec/exec_cmd_line.c\
			$(DIR_SRCS)/exec/get_path.c\
			$(DIR_SRCS)/exec/redirs.c\
			$(DIR_SRCS)/exec/handle_pipes.c\
			$(DIR_SRCS)/exec/exec_utils.c\
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

OBJS	:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))

all : $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@curr=$$(find objs -iname "*.o" | wc -l); \
	total=$$(find srcs -iname "*.c" | wc -l); \
	printf "\e[?25l\rCompiling : \e[1m⟬"; \
	printf "%s" "$$(printf "\e[107m%*s\e[0m" $$curr "")"; \
	printf "%*s" $$(($$total - $$curr)); \
	printf "\e[1m⟭\e[0m %d/%d" $$curr $$total;
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo -e "\n✅ Compilation completed: $(NAME)\e[?25h"

clean :
	@rm -rf $(DIR_OBJS)
	@echo "✅ clean done."

fclean : clean
	@rm -f $(NAME)
	@echo "✅ fclean done."

re : fclean all

.PHONY : all clean fclean re