/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/10/22 12:00:23 by almighty         ###   ########.fr       */
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

static inline bool	count_arg(char **arg, size_t *argv_len, t_env *env)
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
	if (sep != ' ')
		return (create_error(&sep, UNCLOSED_QUOTES_ERR, env));
	return (false);
}

bool	get_argv_len(char *cmd, t_cmd *res, size_t *argv_len, t_env *env)
{
	*argv_len = 0;
	while (!is_end_of_cmd(*cmd, ' '))
	{
		if (*cmd == '<' && *(cmd + 1) == '<')
		{
			if (get_hdoc(&cmd, res, env))
				return (true);
			res->is_fd_in_hdoc = true;
		}
		else if (*cmd == '>' || *cmd == '<')
		{
			go_to_end_of_redir(&cmd, env);
			res->is_fd_in_hdoc = false;
		}
		else if (*cmd != ' ')
			count_arg(&cmd, argv_len, env);
		else
			cmd++;
	}
	return (false);
}
