/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_end_of.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:27:45 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 13:47:03 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline bool	go_to_end_of_arg(char **arg, t_env *env)
{
	char	sep;

	sep = ' ';
	while (!is_end_of_arg(**arg, sep))
	{
		set_sep(&sep, **arg);
		(*arg)++;
	}
	if (sep != ' ')
	{
		create_error(&sep, UNCLOSED_QUOTES_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	go_to_end_of_redir(char **redir, t_env *env)
{
	*redir += 1 + ((**redir == '>' && *((*redir) + 1) == '>')
			|| (**redir == '<' && *((*redir) + 1) == '<'));
	skip_spaces(redir);
	if (is_end_of_arg(**redir, ' '))
	{
		create_error(*redir, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (go_to_end_of_arg(redir, env));
}

inline bool	go_to_end_of_cmd(char **cmd, bool *is_empty,
		size_t *cmd_list_len, t_env *env)
{
	while (!is_end_of_cmd(**cmd, ' '))
	{
		if (**cmd == '>' || **cmd == '<')
		{
			if (go_to_end_of_redir(cmd, env))
				return (true);
			(*cmd_list_len) += *is_empty;
			*is_empty = false;
		}
		else if (**cmd != ' ')
		{
			if (go_to_end_of_arg(cmd, env))
				return (true);
			(*cmd_list_len) += *is_empty;
			*is_empty = false;
		}
		else
			(*cmd)++;
	}
	return (false);
}
