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
	UNEXPECTED_TOKEN_ERR
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
	char			*path;
	char			**argv;
	int				fd_in;
	int				fd_out;
	bool			append_mode;
}	t_cmd;

typedef struct s_env
{
	char	**envp;
	t_cmd	*cmd_list;
	char	*empty_string;
	char	**empty_list;
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

bool	is_var_char(char c);
bool	is_var(char *str, char sep);
bool	get_var(char **name, char **res, t_env *env);
//
bool	is_end_of_cmd(char c, char sep);
bool	is_end_of_arg(char c, char sep);
bool	is_quote(char c);
void	set_sep(char *sep, char c);
char	skip_spaces(char **str);
//
bool	go_to_end_of_redir(char **redir, t_env *env);
bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env);
//
bool	create_error(char *culprit, t_err err, t_env *env);

#endif