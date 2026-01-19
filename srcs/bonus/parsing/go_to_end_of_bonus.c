/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_end_of_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:27:45 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:44 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

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

inline int	go_to_end_of_redir(t_cmd_parsing *cmdp, t_env *env)
{
	bool	is_hdoc;

	is_hdoc = (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<');
	cmdp->str += 1 + ((*(cmdp->str) == '>' && *(cmdp->str + 1) == '>')
			|| is_hdoc);
	skip_spaces(&cmdp->str);
	if (is_end_of_arg(cmdp))
	{
		create_error(cmdp->str, UNEXPECTED_TOKEN_ERR, env);
		return (ERR);
	}
	if (go_to_end_of_arg(cmdp, env))
		return (ERR);
	return (IS_HDOC * is_hdoc);
}
