/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:26:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RABOUSHELL_H
# define RABOUSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <termios.h>

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

# define BLACK	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define SGREEN	"\033[92m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define BOLD	"\033[1m"
# define DIM	"\033[2m"
# define RST	"\033[0m"

typedef unsigned char	t_uchar;
typedef struct s_gl		t_gl;
extern int				g_sig;

typedef enum e_err
{
	SUCCESS,
	ERR,
	PARSING_ERR,
	UNCLOSED_QUOTES_ERR,
	UNEXPECTED_TOKEN_ERR,
	EXEC_ERR,
	CMD_NOT_FOUND_ERR,
	CMD_NOT_EXEC_ERR,
	CMD_FILE_NOT_FOUND_ERR,
	FILE_ERR,
	AMBI_REDIR_ERR,
	BUILTIN_ERR,
	TERM_ERR,
	SYS_ERR,
}	t_err;

typedef enum e_builtin
{
	NOT_BUILTIN,
	CD_BUILTIN,
	ECHO_BUILTIN,
	ENV_BUILTIN,
	EXIT_BUILTIN,
	EXPORT_BUILTIN,
	PWD_BUILTIN,
	UNSET_BUILTIN
}	t_builtin;

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
	char		*path;
	bool		cmd_name_is_path;
	char		**argv;
	t_redir		*redirv;
	size_t		redirv_len;
	int			fd_in;
	int			fd_out;
	t_rtype		fd_in_type;
	t_rtype		fd_out_type;
	t_builtin	builtin;
}	t_cmd;

typedef struct s_gl
{
	t_term	old_term;
	t_term	term;
	t_hist	*history;
	size_t	prompt_len;
	int		win_cols;
	size_t	prev_line_count;
	size_t	prev_line_index;
	bool	update_history;
	bool	is_ctrl;
	t_env	*main_env;
}	t_gl;

typedef struct s_env
{
	char	**envp;
	char	**exportp;
	size_t	envp_len;
	size_t	exportp_len;
	//
	t_gl	get_line_env;
	//
	bool	in_fork;
	pid_t	last_pid;
	//
	t_err	err;
	char	culprit[CULPRIT_LENGTH];
	t_uchar	exit_code;
	bool	end_of_raboushell;
}	t_env;

//
void	set_new_cmd(t_cmd *cmd, t_env *env);
bool	is_empty_cmd(t_cmd *cmd);
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
bool	exec_cmd_line(t_cmd *cmd_list, size_t cmd_list_len, t_env *env);
//
bool	get_line(char **dst, char *prompt, t_gl *env);
//
bool	is_var_char(char c);
void	print_raboushell(void);
//
bool	create_error(char *culprit, t_err err, t_env *env);
void	throw_error(t_env *env);

#endif