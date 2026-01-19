/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shell_parsing_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:38:28 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:08 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

#define EOL	0b00001
#define ARG	0b00010
#define OP	0b00100
// START OF SUBSHELL '('
#define SOS	0b01000
// END OF SUBSHELL ')'
#define EOS	0b10000

static inline bool	check_unexpected_token(char *line, char expected_tokens,
	t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	char			*culprit;

	if ((is_end_of_line(line) && !(expected_tokens & EOL))
		|| (is_control_op(line) && !(expected_tokens & OP))
		|| (*line == '(' && !(expected_tokens & SOS))
		|| (*line == ')' && !(expected_tokens & EOS)))
	{
		create_error(line, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	else if (!(is_end_of_line(line) || is_control_op(line) || *line == '('
			|| *line == ')')
		&& *line != ' ' && !(expected_tokens & ARG))
	{
		init_cmd_parsing(&tmp_cmdp, NULL, line);
		if (!get_raw_arg(&culprit, &tmp_cmdp, true, env))
		{
			create_error(culprit, UNEXPECTED_TOKEN_ERR, env);
			env->free_culprit = true;
		}
		return (true);
	}
	return (false);
}

static inline bool	check_cmd_parsing(char **line, t_env *env)
{
	t_cmd_parsing	cmdp;

	init_cmd_parsing(&cmdp, NULL, *line);
	while (!is_end_of_cmd(&cmdp))
	{
		if (*(cmdp.str) == '>' || *(cmdp.str) == '<')
		{
			if (go_to_end_of_redir(&cmdp, env) == ERR)
				return (true);
		}
		else if (*(cmdp.str) != ' ')
		{
			if (go_to_end_of_arg(&cmdp, env))
				return (true);
		}
		else
			cmdp.str++;
	}
	*line = cmdp.str;
	return (false);
}

static inline bool	check_shell_op_parsing(char **line, char *expected_tokens,
	bool is_in_subshell, t_env *env)
{
	if (is_control_op(*line))
	{
		*line += (**line == '|' && *(*line + 1) != '|')
			+ 2 * ((**line == '|' && *(*line + 1) == '|')
				|| **line == '&');
		*expected_tokens = (!EOL) | ARG | (!OP) | SOS | (!EOS);
	}
	else
	{
		if (check_cmd_parsing(line, env))
			return (true);
		*expected_tokens = (EOL * !is_in_subshell) | ARG | OP | (!SOS)
			| (EOS * is_in_subshell);
	}
	return (false);
}

static inline bool	check_subshell_parsing(char **line, char *expected_tokens,
	bool is_in_subshell, t_env *env)
{
	(*line)++;
	if (check_shell_parsing(line, true, env))
		return (true);
	*expected_tokens = (EOL * !is_in_subshell) | (!ARG) | OP | (!SOS)
		| (EOS * is_in_subshell);
	(*line)++;
	return (false);
}

bool	check_shell_parsing(char **line, bool is_in_subshell, t_env *env)
{
	char	expected_tokens;

	expected_tokens = (EOL * !is_in_subshell) | ARG | (!OP) | SOS | (!EOS);
	while (!is_end_of_shell(*line, expected_tokens & EOS))
	{
		if (check_unexpected_token(*line, expected_tokens, env))
			return (true);
		if (**line == '(')
		{
			if (check_subshell_parsing(line, &expected_tokens, is_in_subshell,
					env))
				return (true);
		}
		else if (**line != ' ')
		{
			if (check_shell_op_parsing(line, &expected_tokens, is_in_subshell,
					env))
				return (true);
		}
		else
			(*line)++;
	}
	return (check_unexpected_token(*line, expected_tokens, env));
}
