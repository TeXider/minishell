/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/12/19 12:37:05 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	get_shell_op(char **line, t_shell_op *shell_op,
			t_env *env);

static inline bool	increment_shell_op(t_shell_op **shell_op, char **line,
	t_env *env)
{
	skip_spaces(line);
	(*shell_op)->op_type += PIPE_OP * (**line == '|' && *(*line + 1) != '|')
		+ AND_OP * (**line == '&')
		+ OR_OP * (**line == '|' && *(*line + 1) == '|');
	*line += ((*shell_op)->op_type == PIPE_OP)
		+ 2 * ((*shell_op)->op_type == AND_OP || (*shell_op)->op_type == OR_OP);
	if (!is_end_of_shell(*line, true) 
		&& safe_shell_op_alloc(&(*shell_op)->next, env))
		return (true);
	*shell_op = (*shell_op)->next;
	return (false);
}

static inline bool	get_subshell(char **line, t_shell_op *shell_op, t_env *env)
{
	if (safe_shell_op_alloc((t_shell_op **) &shell_op->op, env))
		return (true);
	(*line)++;
	shell_op->is_subshell = true;
	if (get_shell_op(line, shell_op->op, env))
		return (true);
	remove_redundant_subshells(shell_op);
	(*line)++;
	return (false);
}

static bool	get_shell_op(char **line, t_shell_op *shell_op,
	t_env *env)
{
	while (!is_end_of_shell(*line, true))
	{
		if (**line != ' ')
		{
			if (**line == '(')
			{
				if (get_subshell(line, shell_op, env))
					return (true);
			}
			else if (get_cmd((t_cmd **) &shell_op->op, line, env))
				return (true);
			if (increment_shell_op(&shell_op, line, env))
				return (true);
		}
		else
			(*line)++;
	}
	return (false);
}

bool	get_shell_line(char *line, t_shell_op **shell_op, t_env *env)
{
	char	*tmp_line;

	tmp_line = line;
	if (check_shell_parsing(&tmp_line, false, env)
		|| safe_shell_op_alloc(shell_op, env))
		return (true);
	return (get_shell_op(&line, *shell_op, env));
}
