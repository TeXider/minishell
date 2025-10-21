/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 09:22:12 by almighty         ###   ########.fr       */
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

# define READ 1

typedef enum e_err
{
	SYS_ERR,
	FILE_ERR,
	CLOSE_ERR,
	AMBI_REDIR_ERR,
	UNCLOSED_QUOTES_ERR,
}	t_err;

typedef enum e_type
{
	HDOC = 1,
	IN = 2,
	OUT = 3,
	APPND = 4
}	t_type;

typedef enum e_rdir
{
	HAS_QUOTES = -1,
}	t_rdir;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	int		fd_in;
	int		fd_out;
	bool	append_mode;
}	t_cmd;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_env
{
	char	**envp;
	size_t	envp_len;
	t_cmd	**cmd_list;
	char	**path_list;
	char	*empty_string;
}	t_env;

typedef struct s_get_arg_core
{
	char	*curr_str;
	bool	in_var;
	char	sep;
}	t_get_arg_core;

bool	is_var_char(char c);
bool	is_var(char *str, char sep);
bool	get_var(char **name, char **res, t_env *env);
//
bool	get_arg(char **arg, t_cmd *res, size_t *arg_i, t_env *env);
//
bool	get_arg_expand_len(char **arg, size_t *len, char sep, t_env *env);
bool	arg_expand(t_get_arg_core *gac, char **argv_ptr, char **arg, t_env *env);
//
bool	is_end_of_cmd(char c, char sep);
bool	is_end_of_arg(char c, char sep);
bool	is_quote(char c);
void	set_sep(char *sep, char c);
char	skip_spaces(char **str);
//
bool	safe_challoc(char **dst, size_t len, t_env *env);
//
bool	open_hdoc(char *delimiter, bool has_quotes, t_env *env);
bool	create_error(char *culprit, t_err ctxt, t_env *env);

void print_str(char *str);

#endif