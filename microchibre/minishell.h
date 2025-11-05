/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/11/04 14:49:34 by tpanou-d         ###   ########.fr       */
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

# define READ 1
# define HAS_QUOTES -1
# define STD_IN 0
# define STD_OUT 1
# define FD_ERR 2
# define FD_NULL -1
# define P_READ 0
# define P_WRITE 1
# define CULPRIT_LENGTH 32

extern bool	g_sigint;

typedef enum e_err
{
	SYS_ERR = 1,
	EXEC_ERR,
	FILE_ERR,
	AMBI_REDIR_ERR,
	UNCLOSED_QUOTES_ERR,
	UNEXPECTED_TOKEN_ERR,
}	t_err;

typedef enum e_type
{
	HDOC = 1,
	IN = 2,
	OUT = 3,
	APPND = 4,
}	t_type;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**redirs;
	int		fd_in;
	int		fd_out;
	bool	is_fd_in_hdoc;
	bool	is_fd_in_pipe;
	bool	is_fd_out_pipe;
	bool	append_mode;
	char	*start_ptr;
}	t_cmd;

typedef struct s_env
{
	char	**envp;
	char	*empty_string;
	char	**empty_list;
	pid_t	last_pid;
	t_err	err;
	char	culprit[CULPRIT_LENGTH];
}	t_env;

typedef struct s_get_redir_name_len
{
	bool	has_arg;
	bool	var_is_sep;
	char	sep;
}	t_get_redir_name_len;

typedef struct s_get_redir_name
{
	size_t	len;
	char	sep;
	bool	has_quotes;
	size_t	i;
}	t_get_redir_name;

typedef struct s_get_arg_core
{
	char	*curr_str;
	bool	in_var;
	char	sep;
}	t_get_arg_core;

typedef struct s_pipes
{
	int		pipe_fds[2];
	int		next_pipe_fds[2];
	bool	is_next_pipe;
	int		fd_read;
	int		fd_write;
}	t_pipes;

bool	is_var_char(char c);
bool	is_var(char *str, char sep);
bool	get_var(char **name, char **res, t_env *env);
//
void	set_new_cmd(t_cmd *cmd, t_env *env);
bool	is_empty_cmd(t_cmd *cmd);
//
bool	is_end_of_cmd(char c, char sep);
bool	is_end_of_arg(char c, char sep);
bool	is_quote(char c);
void	set_sep(char *sep, char c);
void	skip_spaces(char **str);
//
bool	go_to_end_of_arg(char **arg, t_env *env);
bool	go_to_end_of_redir(char **redir, t_env *env);
bool	go_to_end_of_cmd(char **cmd, bool *is_empty,
			size_t *cmd_list_len, t_env *env);
bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env);
//
bool	get_argv_len(char *cmd, size_t *argv_len, t_cmd *res, t_env *env);
bool	get_arg(char **arg, t_cmd *res, size_t *arg_i, t_env *env);
//
bool	get_cmd(char **cmd, t_cmd *res, t_env *env);
bool	get_cmd_line(char **line, t_cmd **cmd_list, t_env *env);
//
void	free_data(t_cmd *cmd, char *line, t_env *env);
bool	safe_challoc(char **dst, size_t len, t_env *env);
bool	safe_lalloc(char ***dst, size_t len, t_env *env);
bool	safe_cmdlalloc(t_cmd **dst, size_t len, t_env *env);
//
bool	get_arg_expand_len(char **arg, size_t *len, char sep, t_env *env);
bool	arg_expand(t_get_arg_core *gac, char **argv_ptr, char **arg,
			t_env *env);
void	redir_expand(char **redir, char *name,
			t_get_redir_name *grn, t_env *env);
bool	get_redir_expand_len(char **redir, size_t *len,
			t_get_redir_name_len *grnl, t_env *env);
//
bool	get_redir(char **redir, t_cmd *res, t_env *env);
int		open_redir(char *name, t_type type, bool has_quotes, t_env *env);
void	close_prev_redir(t_cmd *cmd, t_type type);
bool	handle_redir_err(char *redir, t_err status, t_env *env);
void	safe_close(int *fd);
//
bool	repipe(int pipes_fds[2], bool is_last_cmd, t_env *env);
void	init_pipes(t_pipes *pipes);
void	close_pipes(t_pipes *pipes);
bool	handle_pipes(t_pipes *pipes, bool is_last_cmd, t_env *env);
//
bool	exec_cmd_line(char **line, size_t cmd_count, t_env *env);
//
int		open_hdoc(char *delimiter, bool has_quotes, t_env *env);
bool	create_error(char *culprit, t_err err, t_env *env);
void	throw_error(t_env *env);

#endif