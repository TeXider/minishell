/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_redirv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/11/11 10:40:04 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	go_through_arg(t_cmd_parsing *cmdp, t_env *env)
{
	bool	is_empty;

	is_empty = true;
	cmdp->sep = ' ';
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		if (!cmdp->in_expand && cmdp->sep != '"' && is_var(cmdp))
			expand(cmdp, env);
		else
		{
			is_empty &= (*(cmdp->str) == ' ');
			cmdp->str++;
		}
		if (cmdp->in_expand && !*(cmdp->str))
			exit_expand(cmdp);
	}
	return (is_empty);
}

bool	get_argv_redirv(t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;

	tmp_str = cmdp->str;
	while (!is_end_of_cmd(cmdp))
	{
		if (!cmdp->in_expand && (*(cmdp->str) == '>' || *(cmdp->str) == '<'))
		{
			go_to_end_of_redir(cmdp, env);
			cmdp->cmd->redirv_len++;
		}
		else if (*(cmdp->str) != ' ')
			cmdp->argv_len += !go_through_arg(cmdp, env);
		else
			cmdp->str++;
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	cmdp->str = tmp_str;
	if (safe_lalloc(&cmdp->cmd->argv, cmdp->argv_len, env)
		|| safe_malloc((void **)&cmdp->cmd->redirv,
			sizeof(t_redir) * cmdp->cmd->redirv_len, env))
		return (true);
	return (false);
}
