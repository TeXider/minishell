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

bool	is_var_char(char c);
bool	is_var(char *str, char sep);
int		get_var(char **name, t_var *res, t_env *env);
//
bool	is_end_of_cmd(char c, char sep);
bool	is_end_of_arg(char c, char sep);
bool	is_quote(char c);
bool	str_eq(char *str1, char *str2, size_t len);
void	set_sep(char *sep, char c);
char	skip_spaces(char **str);
//
bool	safe_challoc(char **dst, size_t len, t_env *env);
//
void	redir_expand(char **redir, char *name,
				t_get_redir_name *grn, t_env *env);
bool	get_redir_expand_len(char **redir, size_t *len,
				t_get_redir_name_len *grnl, t_env *env);
//
bool	get_redir(char **redir, t_cmd *res, t_env *env);
int		open_redir(char *name, t_type type, bool has_quotes, t_env *env);
bool	close_prev_redir(t_cmd *cmd, t_type type, t_env *env);
bool	handle_redir_err(char *redir, t_err status, t_env *env);
//
bool	open_hdoc(char *delimiter, bool has_quotes, t_env *env);
bool	create_error(char *culprit, t_err ctxt, t_env *env);

#endif