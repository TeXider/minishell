/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_redirv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2026/01/15 14:41:38 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

#define IS_EMPTY	true

static bool	go_through_arg(t_cmd_parsing *cmdp, t_env *env)
{
	bool	is_empty;

	is_empty = true;
	cmdp->sep = ' ';
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		if (cmdp->sep != '"' && is_expand(cmdp))
			expand(cmdp, env);
		else
		{
			is_empty &= (*(cmdp->str) == ' ');
			cmdp->str++;
		}
		if (is_end_of_expand(cmdp))
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
			cmdp->cmd->redirv_len += (go_to_end_of_redir(cmdp, env) != IS_HDOC);
		else if (*(cmdp->str) != ' ')
			cmdp->argv_len += (go_through_arg(cmdp, env) != IS_EMPTY);
		else
			cmdp->str++;
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	cmdp->str = tmp_str;
	if (safe_lalloc(&cmdp->cmd->argv, cmdp->argv_len, env)
		|| safe_malloc((void **)&cmdp->cmd->redirv,
			sizeof(t_redir) * (cmdp->cmd->redirv_len + 1), env))
		return (true);
	cmdp->curr_redir = cmdp->cmd->redirv;
	cmdp->curr_redir->name = NULL;
	cmdp->curr_redir->type = EMPTY_REDIR;
	return (false);
}
