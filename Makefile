NAME            := minishell
CC                      := cc
CFLAGS          := -Wall -Wextra -Werror -g


DIR_SRCS                := srcs
DIR_OBJS                := objs

SRCS 	:=	$(DIR_SRCS)/main/create_error.c\
			$(DIR_SRCS)/main/main.c\
			$(DIR_SRCS)/main/exit_raboushell.c\
			$(DIR_SRCS)/main/throw_error.c\
			$(DIR_SRCS)/main/utils.c\
			$(DIR_SRCS)/main/memory.c\
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
			$(DIR_SRCS)/exec/open_redirs.c\
			$(DIR_SRCS)/exec/pipes.c\
			$(DIR_SRCS)/builtins/builtin_cd.c\
			$(DIR_SRCS)/builtins/builtin_echo.c\
			$(DIR_SRCS)/builtins/builtin_env.c\
			$(DIR_SRCS)/builtins/builtin_export.c\
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
			$(DIR_SRCS)/get_line/output_editing.c\

OBJS 	:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))

all : $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "✅ Compilation completed: $(NAME)"

clean :
	@rm -rf $(DIR_OBJS)
	@$(MAKE) -s -C $(DIR_LIBFT) clean
	@echo "✅ clean done."

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(DIR_LIBFT) fclean
	@echo "✅ fclean done."

re : fclean all

.PHONY : all clean fclean re