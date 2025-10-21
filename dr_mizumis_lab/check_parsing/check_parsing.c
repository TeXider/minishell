/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:27:45 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 12:04:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	go_to_end_of_arg(char **arg, t_env *env)
{
	char	sep;
	
	sep = ' ';
	while (!is_end_of_arg(**arg, sep))
	{
		set_sep(&sep, **arg);
		(*arg)++;
	}
	if (sep != ' ')
		return (create_error(&sep, UNCLOSED_QUOTES_ERR, env));
	return (false);
}

inline bool	go_to_end_of_redir(char **redir, t_env *env)
{
	char	sep;
	
	*redir += 1 + ((**redir == '>' && *((*redir) + 1) == '>')
			|| (**redir == '<' && *((*redir) + 1) == '<'));
	skip_spaces(redir);
	if (is_end_of_arg(**redir, ' '))
		return (create_error(*redir, UNEXPECTED_TOKEN_ERR, env));
	sep = ' ';
	while (!is_end_of_arg(**redir, sep))
	{
		set_sep(&sep, **redir);
		(*redir)++;
	}
	if (sep != ' ')
		return (create_error(&sep, UNCLOSED_QUOTES_ERR, env));
	return (false);
}

static inline bool	go_to_end_of_cmd(char **cmd, bool *is_empty,
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

bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env)
{
	bool	has_pipe;
	bool	is_empty;
	
	*cmd_list_len = 0;
	has_pipe = false;
	is_empty = true;
	while (*line && *line != '\n')
	{
		if (go_to_end_of_cmd(&line, &is_empty, cmd_list_len,
			env))
			return (true);
		if (is_empty && (*line == '|' || has_pipe))
			return (create_error(line, UNEXPECTED_TOKEN_ERR, env));
		is_empty = true;
		has_pipe = (*line == '|');
		line += (has_pipe);
	}
	if (has_pipe && is_empty)
		return (create_error(line, UNEXPECTED_TOKEN_ERR, env));
	return (false);
}
