/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/12/08 10:39:31 by almighty         ###   ########.fr       */
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
# define ETXT	"\033[1;4;31m"
# define RST	"\033[0m"

typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;

# define SIGNAL_EXIT 1
# define SIGNAL_INT 2

extern int				g_sig;

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
	char	culprit[CULPRIT_LENGTH];
	t_uchar	exit_code;
	char	exit_code_str[4];
	bool	end_of_raboushell;
}	t_env;

void	raboushell(char *input, t_env *env);
//
void	safe_free(void **ptr);
void	free_data(t_cmd *cmd, char *line, t_env *env);
bool	safe_challoc(char **dst, size_t len, t_env *env);
bool	safe_lalloc(char ***dst, size_t len, t_env *env);
bool	safe_malloc(void **dst, size_t len, t_env *env);
//
void	init_signals(void);
void	handle_sigint(t_env *env);
//
bool	get_line(char **dst, char *prompt, t_gl *env);
void	safe_free_history(t_gl *env);
//
bool	is_var_char(char c);
void	print_raboushell(void);
void	print_str(char *str);
void	set_exit_code(t_uchar exit_code, t_env *env);
void	safe_close(int *fd, int new_fd);
void	print_ushort(t_uint num);
//
void	create_error(char *culprit, t_err err, t_env *env);
void	throw_error(t_env *env);
void	exit_raboushell(t_env *env);

#endif