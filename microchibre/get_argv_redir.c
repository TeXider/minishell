/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 09:52:27 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	count_args_in_var(char **arg, size_t *argv_len,
		bool *var_is_sep, t_env *env)
{
	char	*var;

	if (get_var(arg, &var, env))
		return ;
	while (*var)
	{
		*argv_len += (*var_is_sep && *var != ' ');
		*var_is_sep = (*var == ' ');
		var++;
	}
}

static inline void	count_arg(char **arg, size_t *argv_len, t_env *env)
{
	char	sep;
	bool	var_is_sep;

	var_is_sep = true;
	sep = ' ';
	while (!is_end_of_arg(**arg, sep))
	{
		set_sep(&sep, **arg);
		if (sep == ' ' && **arg == '$' && is_var_char(*(*arg + 1)))
			count_args_in_var(arg, argv_len, &var_is_sep, env);
		else
		{
			*argv_len += var_is_sep;
			var_is_sep = false;
		}
		(*arg)++;
	}
}

static inline bool	count_arg_redir(char **cmd_str, t_cmd *res,
	t_get_argv_redirs *ar, t_env *env)
{
	if (**cmd_str == '<' && *(*cmd_str + 1) == '<')
	{
		if (get_hdoc(cmd_str, res, env))
			return (true);
		res->is_fd_in_hdoc = true;
	}
	else if (**cmd_str == '>' || **cmd_str == '<')
	{
		go_to_end_of_redir(cmd_str, env);
		ar->redirs_len++;
		res->is_fd_in_hdoc = false;
	}
	else if (**cmd_str != ' ')
		count_arg(cmd_str, &ar->argv_len, env);
	else
		(*cmd_str)++;
	return (false);
}

bool	get_argv_redir(char *cmd_str, t_cmd *res, t_env *env)
{
	t_get_argv_redirs	ar;
	
	ar.argv_len = 0;
	ar.redirs_len = 0;
	while (!is_end_of_cmd(*cmd_str, ' '))
		if (count_arg_redir(&cmd_str, res, &ar, env))
			return (true);
	if (safe_lalloc(&res->argv, ar.argv_len, env)
		|| safe_lalloc(&res->redirs, ar.redirs_len, env))
		return (true);
	return (false);
}
