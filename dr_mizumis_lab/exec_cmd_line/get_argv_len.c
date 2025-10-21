/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/10/09 09:50:21 by almighty         ###   ########.fr       */
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

bool	get_argv_len(char *cmd, size_t *argv_len, t_env *env)
{
	*argv_len = 0;
	while (!is_end_of_cmd(*cmd, ' '))
	{
		if (*cmd == '>' || *cmd == '<')
		{
			if (go_to_end_of_redir(&cmd, env))
				return (true);
		}
		else if (*cmd != ' ')
		{
			if (count_arg(&cmd, argv_len, env))
				return (true);
		}
		else
			cmd++;
	}
	return (false);
}
