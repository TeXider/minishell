/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 09:19:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>

# define READ 1
# define HAS_QUOTES -1
# define IS_HDOC -1
# define IS_EMPTY true
# define STD_IN 0
# define STD_OUT 1
# define FD_ERR 2
# define FD_NULL -1
# define P_READ 0
# define P_WRITE 1
# define CULPRIT_LENGTH 32

# define VAR_INEXISTANT 0
# define VAR_IN_EXPORTP 1
# define VAR_IN_ENVP 2
# define TO_EXPORTP 0
# define TO_ENVP 1
# define TO_ENVP_APPND 2

typedef unsigned char	t_uchar;
typedef struct termios	t_term;
extern int				g_sig;

typedef enum e_err
{
	SUCCESS,
	ERR,
	SYS_ERR,
	TERM_ERR,
	EXEC_ERR,
	FILE_ERR,
	AMBI_REDIR_ERR,
	UNCLOSED_QUOTES_ERR,
	UNEXPECTED_TOKEN_ERR,
	BUILTIN_ERR,
}	t_err;

typedef enum e_builtin_err
{
	ECHO_ERR,
	CD_ERR,
	PWD_ERR,
	EXPORT_ERR,
	UNSET_ERR,
	ENV_ERR,
	EXIT_ERR
}	t_builtin_err;

typedef enum e_builtin_err_ctxt
{
	INVALID_PARAM,
	TOO_MANY_PARAMS
}	t_builtin_err_ctxt;

typedef enum e_rtype
{
	EMPTY_REDIR,
	HDOC,
	IN,
	OUT,
	APPND,
	PIPE,
	STD,
	AMBI_REDIR
}	t_rtype;

typedef struct s_redir
{
	char	*name;
	t_rtype	type;
}	t_redir;

typedef struct s_cmd
{
	char	*path;
	bool	cmd_name_is_path;
	char	**argv;
	t_redir	*redirv;
	size_t	redirv_len;
	int		fd_in;
	int		fd_out;
	t_rtype	fd_in_type;
	t_rtype	fd_out_type;
}	t_cmd;

typedef struct s_line
{
	char			curr_char;
	char			*buffer;
	size_t			index;
	size_t			count;
	size_t			len;
}	t_line;

typedef struct s_hist
{
	t_line			*edit_line;
	t_line			*og_line;
	struct s_hist	*next;
	struct s_hist	*prev;
}	t_hist;

typedef struct s_env
{
	char	**envp;
	char	**exportp;
	size_t	envp_len;
	size_t	exportp_len;
	char	empty_string[1];
	char	*empty_list[2];
	//
	t_term	old_term;
	t_term	term;
	t_hist	*history;
	size_t	prompt_len;
	int		win_cols;
	size_t	prev_line_count;
	size_t	prev_line_index;
	bool	update_history;
	bool	is_ctrl;
	//
	pid_t	last_pid;
	t_err	err;
	char	culprit[CULPRIT_LENGTH];
	t_uchar	exit_code;
	bool	exit_cmd;
}	t_env;

typedef struct s_var_info
{
	char	stat;
	char	operation;
	size_t	envp_index;
	size_t	exportp_index;
}	t_var_info;

typedef struct s_cmd_parsing
{
	char	*str;
	char	*saved_str;
	bool	in_expand;
	t_cmd	*cmd;
	size_t	redirv_i;
	size_t	argv_i;
	size_t	argv_len;
	t_redir	*curr_redir;
	bool	fd_in_is_hdoc;
	char	*curr_arg;
	char	sep;
}	t_cmd_parsing;

typedef struct s_pipes
{
	int		pipe_fds[2];
	int		next_pipe_fds[2];
	bool	is_next_pipe;
	int		fd_read;
	int		fd_write;
}	t_pipes;

bool	is_var_char(char c);
bool	is_var(t_cmd_parsing *cmdp);
bool	is_end_of_expand(t_cmd_parsing *cmdp);
//
void	set_new_cmd(t_cmd *cmd, t_env *env);
bool	is_empty_cmd(t_cmd *cmd);
//
bool	is_end_of_cmd(t_cmd_parsing *cmdp);
bool	is_end_of_arg(t_cmd_parsing *cmdp);
bool	is_end_of_redir(t_cmd_parsing *cmdp);
bool	is_quote(char c);
void	set_sep(t_cmd_parsing *cmdp);
void	skip_spaces(char **str);
void	simple_init_cmd_parsing(t_cmd_parsing *cmdp);
void	init_cmd_parsing(t_cmd_parsing *cmdp, char *line);
bool	change_of_sep(t_cmd_parsing *cmdp);
bool	is_end_of_hdoc(char *del, char *line);
bool	str_eq(char *str1, char *str2);
void	reset_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd);
//
bool	go_to_end_of_arg(t_cmd_parsing *cmdp, t_env *env);
int		go_to_end_of_redir(t_cmd_parsing *cmdp, t_env *env);
bool	go_to_end_of_cmd(t_cmd_parsing *cmdp, size_t *cmd_list_len,
			bool *is_empty, t_env *env);
//
bool	get_argv_redirv(t_cmd_parsing *cmdp, t_env *env);
bool	get_arg(t_cmd_parsing *cmdp, t_env *env);
bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env);
//
bool	get_cmd_line(char *line, t_cmd **cmd_list, size_t *cmd_list_len,
			t_env *env);
//
void	safe_free(void **ptr);
void	free_data(t_cmd *cmd, char *line, t_env *env);
bool	safe_challoc(char **dst, size_t len, t_env *env);
bool	safe_lalloc(char ***dst, size_t len, t_env *env);
bool	safe_malloc(void **dst, size_t len, t_env *env);
//
void	expand(t_cmd_parsing *cmdp, t_env *env);
void	exit_expand(t_cmd_parsing *cmdp);
//
bool	get_redir_name_len(char *redir, size_t *len, bool is_hdoc, t_env *env);
bool	get_redir(t_cmd_parsing *cmdp, t_env *env);
void	safe_close(int *fd, int new_fd);
//
bool	repipe(int pipes_fds[2], bool is_last_cmd, t_env *env);
void	init_pipes(t_pipes *pipes);
void	close_pipes(t_pipes *pipes);
bool	handle_pipes(t_pipes *pipes, size_t cmd_list_i, size_t cmd_list_len,
			t_env *env);
//
bool	get_path(t_cmd *cmd, t_env *env);
bool	open_redirs(t_cmd *cmd, t_env *env);
bool	exec_cmd_line(t_cmd *cmd_list, size_t cmd_list_len, t_env *env);
//
bool	get_line(char **dst, char *prompt, t_env *env);
//
void	builtin_echo(char **args);
void	builtin_env(t_env *env);
bool	builtin_exit(char **args, t_env *env);
bool	builtin_export(char **args, t_env *env);
bool	builtin_pwd(t_env *env);
bool	builtin_unset(char **args, t_env *env);
bool	convert_export_to_var(char *export, char **var_dst,
	t_var_info *var_info, t_env *env);
bool	add_to_envp(char *new_var, t_env *env);
bool	remove_from_envp(size_t var_index, t_env *env);
bool	add_to_exportp(char *new_var, t_env *env);
bool	remove_from_exportp(size_t var_index, t_env *env);
void	find_var(char *var, t_var_info *var_info, t_env *env);
//
bool	create_error(char *culprit, t_err err, t_env *env);
void	throw_error(t_env *env);

#endif