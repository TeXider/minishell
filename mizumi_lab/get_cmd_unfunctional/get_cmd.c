/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/10/01 07:42:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_arg(char **arg, t_cmd *res, size_t *arg_i, t_env *env)
{
	char	sep;
	int		is_empty;

	is_empty = 1;
	while (!is_end_of_arg(**arg, sep))
	{
		set_sep(&sep, **arg);
		if (sep != '\'' && **arg == '$' && is_var_char(*(*arg + 1)))
			is_empty &= check_var_empty(arg, env);
		else
			is_empty &= (**arg == ' ');
		(*arg)++;
	}
	return (2 * (sep != ' ') | is_empty);
}

bool	get_cmd(char **cmd, t_cmd *res, t_env *env)
{
	size_t	argv_len;
	size_t	arg_i;

	if (get_argv_len(*cmd, &argv_len, env)
		|| set_lalloc(&(res->argv), argv_len, env))
		return (false);
	arg_i = 0;
	while (!is_end_of_cmd(**cmd, ' '))
	{
		if (**cmd == '>' || **cmd == '<')
		{
			if (get_redir(cmd, res, env))
				return (get_final_hdocs(cmd, env));
		}
		else if (**cmd != ' ')
		{
			if (get_arg(cmd, res, &arg_i, env))
				return (true);
		}
		else
			(*cmd)++;
	}
	return (false);
}
