/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_end_of.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:27:45 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 08:58:11 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline bool	go_to_end_of_arg(t_cmd_parsing *cmdp, t_env *env)
{
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		cmdp->str++;
	}
	if (cmdp->sep != ' ')
	{
		create_error(&cmdp->sep, UNCLOSED_QUOTES_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	go_to_end_of_redir(t_cmd_parsing *cmdp, t_env *env)
{
	cmdp->str += 1 + ((*(cmdp->str) == '>' && *(cmdp->str + 1) == '>')
			|| (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<'));
	skip_spaces(&cmdp->str);
	if (is_end_of_arg(cmdp))
	{
		create_error(cmdp->str, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (go_to_end_of_arg(cmdp, env));
}

inline bool	go_to_end_of_cmd(t_cmd_parsing *cmdp, size_t *cmd_list_len,
	bool *is_empty, t_env *env)
{
	while (!is_end_of_cmd(cmdp))
	{
		if (*(cmdp->str) == '>' || *(cmdp->str) == '<')
		{
			if (go_to_end_of_redir(cmdp, env))
				return (true);
			(*cmd_list_len) += *is_empty;
			*is_empty = false;
		}
		else if (*(cmdp->str) != ' ')
		{
			if (go_to_end_of_arg(cmdp, env))
				return (true);
			(*cmd_list_len) += *is_empty;
			*is_empty = false;
		}
		else
			cmdp->str++;
	}
	if (*is_empty && (*(cmdp->str) == '|'))
	{
		create_error(cmdp->str, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (false);
}
