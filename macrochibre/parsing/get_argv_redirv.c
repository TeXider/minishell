/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_redirv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 13:46:55 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	count_args_in_var(t_cmd_parsing *cmdp, bool *var_is_sep,
	t_env *env)
{
	char	*var;

	if (get_var(&cmdp->str, &var, env))
		return ;
	while (*var)
	{
		cmdp->argv_len += (*var_is_sep && *var != ' ');
		*var_is_sep = (*var == ' ');
		var++;
	}
}

static inline void	count_arg(t_cmd_parsing *cmdp, t_env *env)
{
	char	sep;
	bool	var_is_sep;

	var_is_sep = true;
	sep = ' ';
	while (!is_end_of_arg(*(cmdp->str), sep))
	{
		set_sep(&sep, *(cmdp->str));
		if (sep == ' ' && *(cmdp->str) == '$' && is_var_char(*(cmdp->str + 1)))
			count_args_in_var(cmdp, &var_is_sep, env);
		else
		{
			cmdp->argv_len += var_is_sep;
			var_is_sep = false;
		}
		cmdp->str++;
	}
}

static inline bool	count_arg_redir(t_cmd_parsing *cmdp, t_env *env)
{
	if (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<')
	{
		if (get_hdoc(cmdp, env))
			return (true);
		cmdp->cmd->is_fd_in_hdoc = true;
	}
	else if (*(cmdp->str) == '>' || *(cmdp->str) == '<')
	{
		cmdp->cmd->is_fd_in_hdoc = (*(cmdp->str) != '<');
		go_to_end_of_redir(&cmdp->str, env);
		cmdp->redirv_len++;
	}
	else if (*(cmdp->str) != ' ')
		count_arg(cmdp, env);
	else
		cmdp->str++;
	return (false);
}

bool	get_argv_redirv(t_cmd_parsing *cmdp, t_env *env)
{
	while (!is_end_of_cmd(*(cmdp->str), ' '))
		if (count_arg_redir(cmdp, env))
			return (true);
	if (safe_lalloc(&cmdp->cmd->argv, cmdp->argv_len, env)
		|| safe_lalloc(&cmdp->cmd->redirv, cmdp->redirv_len, env))
		return (true);
	return (false);
}
