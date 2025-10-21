/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:25:05 by almighty          #+#    #+#             */
/*   Updated: 2025/10/09 09:50:21 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>

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
	t_var	**envp;
	size_t	envp_len;
	t_cmd	**cmd_list;
	char	**path_list;
	char	*empty_string;
}	t_env;

bool	is_var_char(char c);
int		get_var(char **name, t_var *res, t_env *env);
bool	check_var_empty(char **var_str, t_env *env);
bool	check_ambiguous_var(char **var_str, t_env *env);
int		check_var_validity(char **var_str, t_env *env);
//
bool	is_end_of_cmd(char c, char sep);
bool	is_end_of_arg(char c, char sep);
bool	str_eq(char *str1, char *str2, size_t len);
void	set_sep(char *sep, char c);
char	skip_spaces(char **str);
//
bool	go_to_end_of_redir(char **redir, t_env *env);
bool	count_arg(char **arg, size_t *argv_len, t_env *env);
bool	get_argv_len(char *cmd, size_t *argv_len, t_env *env);

#endif