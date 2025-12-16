/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:38:28 by almighty          #+#    #+#             */
/*   Updated: 2025/12/15 10:41:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	check_line_parsing(char **line, t_env *env);
bool	check_shell_op_parsing(char **line, bool *is_empty,
	bool *has_op, t_env *env);

static inline void	handle_unexpected_arg_error(char *line, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	char			*culprit;

	tmp_cmdp.str = line;
	tmp_cmdp.sep = ' ';
	if (!get_raw_arg(&culprit, &tmp_cmdp, env))
	{
		create_error(culprit, UNEXPECTED_TOKEN_ERR, env);
		env->free_culprit = true;
	}
}

static inline bool	check_cmd_parsing(char **line, t_env *env)
{
	t_cmd_parsing	cmdp;
	bool			is_empty;

	init_cmd_parsing(&cmdp, *line);
	is_empty = true;
	while (!is_end_of_cmd(&cmdp))
	{
		if (*(cmdp.str) == '>' || *(cmdp.str) == '<')
		{
			if (go_to_end_of_redir(&cmdp, env) == ERR)
				return (true);
			is_empty = false;
		}
		else if (*(cmdp.str) != ' ')
		{
			if (go_to_end_of_arg(&cmdp, env))
				return (true);
			is_empty = false;
		}
		else
			cmdp.str++;
	}
	if (is_empty && !is_end_of_line(*line))
	{
		create_error(cmdp.str, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	*line = cmdp.str;
	return (false);
}

inline bool	check_shell_op_parsing(char **line, bool *is_empty,
	bool *has_op, t_env *env)
{
	if (!*is_empty && !*has_op)
	{
		if (**line == '(' || **line == ')')
			create_error(*line, UNEXPECTED_TOKEN_ERR, env);
		else
			handle_unexpected_arg_error(*line, env);
		return (true);
	}
	if (**line == '(')
	{
		(*line)++;
		if (check_line_parsing(line, env))
			return (true);
		if (**line == ')')
			(*line)++;
		else
		{
			create_error(*line, UNEXPECTED_TOKEN_ERR, env);
			return (true);
		}
	}
	else if (check_cmd_parsing(line, env))
		return (true);
	*is_empty = false;
	return (false);
}

bool	check_op(char **line, bool *is_empty, bool *has_op, t_env *env)
{
	if (is_shell_op(*line))
	{
		if (*is_empty)
		{
			create_error(*line, UNEXPECTED_TOKEN_ERR, env);
			return (true);
		}
		*line = *line + (**line == '|' &&  *(*line + 1) != '|')
			+ 2 * ((**line == '|' && *(*line + 1) == '|') 
				|| **line == '&');
		*has_op = true;
		*is_empty = true;
	}
	return (false);
}

inline bool	check_line_parsing(char **line, t_env *env)
{
	bool	is_empty;
	bool	has_op;

	is_empty = true;
	has_op = false;
	while (!is_end_of_subshell(*line))
	{
		if (check_op(line, &is_empty, &has_op, env))
			return (true);
		else if (**line != ' ')
		{
			if (check_shell_op_parsing(line, &is_empty, &has_op, env))
				return (true);
		}
		else
			(*line)++;
	}
	if (is_empty && (!is_end_of_line(*line) || has_op))
	{
		create_error(*line, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (false);
}
