/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_redirv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/11/06 16:45:18 by almighty         ###   ########.fr       */
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
	while (cmdp->in_expand || !is_end_of_cmd(cmdp))
	{
		if (!cmdp->in_expand && (*(cmdp->str) == '>' || *(cmdp->str) == '<'))
		{
			go_to_end_of_redir(cmdp, env);
			cmdp->redirv_len++;
		}
		else if (*(cmdp->str) != ' ')
			cmdp->argv_len += !go_through_arg(cmdp, env);
		else
			cmdp->str++;
		if (cmdp->in_expand && !*(cmdp->str))
			exit_expand(cmdp);
	}
	cmdp->str = tmp_str;
	return (false);
}
