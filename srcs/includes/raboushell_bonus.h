/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 22:28:23 by almighty         ###   ########.fr       */
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
# include <sys/types.h>
# include "cmd_struct.h"
# include "get_line_struct.h"

# define STD_IN				0
# define STD_OUT			1
# define FD_ERR				2
# define FD_NULL			-1
# define P_READ				0
# define P_WRITE			1
# define CULPRIT_LENGTH		32

# define BLACK	"\e[30m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define SGREEN	"\e[92m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"
# define BCYAN	"\e[1;96m"
# define WHITE	"\e[37m"
# define BOLD	"\e[1m"
# define DIM	"\e[2m"
# define ETXT	"\e[1;4;31m"
# define RST	"\e[0m"
# define RABOU	"\e[0;1;92m"
# define SHELL	"\e[0;1;96m"

typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;
typedef short int			t_sint;

# define SIGNAL_EXIT	1
# define SIGNAL_INT		2

extern int					g_sig;

typedef enum e_err
{
	SUCCESS,
	ERR,
	PARSING_ERR,
	UNCLOSED_QUOTES_ERR,
	UNEXPECTED_TOKEN_ERR,
	EXEC_ERR,
	FILE_ERR,
	AMBI_REDIR_ERR,
	CMD_NOT_FOUND_ERR,
	CMD_NOT_EXEC_ERR,
	CMD_IS_DIR_ERR,
	CMD_FILE_NOT_FOUND_ERR,
	BUILTIN_ERR,
	SYS_ERR,
	TERM_ERR,
	FATAL_SYS_ERR,
}	t_err;

typedef struct s_env
{
	/*ENVIRONMENT VARIABLES*/
	char	**envp;
	char	**exportp;
	size_t	envp_len;
	size_t	exportp_len;
	/*GET LINE*/
	t_gl	get_line_env;
	/*EXECUTION*/
	bool	in_fork;
	pid_t	last_pid;
	int		saved_std_in;
	int		saved_std_out;
	int		discarded_pipe_fd;
	/*ERROR HANDLING*/
	int		children_count;
	t_err	err;
	char	*culprit;
	bool	free_culprit;
	char	*err_msg;
	t_uchar	exit_code;
	char	exit_code_str[4];
	bool	end_of_raboushell;
}	t_env;

/* RABOUSHELL */

void	raboushell(t_env *env);
void	exit_raboushell(t_env *env);

/* MEMORY */

void	safe_free(void **ptr);
void	free_data(t_cmd *cmd, char *line, t_env *env);
bool	safe_challoc(char **dst, size_t len, t_env *env);
bool	safe_lalloc(char ***dst, size_t len, t_env *env);
bool	safe_malloc(void **dst, size_t len, t_env *env);

/* SIGNALS */

void	init_signals(void);
void	handle_sigint(t_env *env);

/* GET_LINE */

bool	get_prompt(char **dst, t_env *env);
bool	get_line(char **dst, char *prompt, t_gl *env);
void	safe_free_history(t_gl *env);

/* UTILS */

bool	is_var_char(char c);
void	print_raboushell(void);
void	print_str(char *str);
void	set_exit_code(t_uchar exit_code, t_env *env);
void	safe_close(int *fd, int new_fd);
void	print_uint(t_uint num);

/* MEMORY */

bool	safe_shell_op_alloc(t_shell_op **dst, t_env *env);
bool	safe_cmd_alloc(t_cmd **dst, t_env *env);

/* ERROR HANDLING */

void	create_error(char *culprit, t_err err, t_env *env);
void	throw_error(t_env *env);

#endif