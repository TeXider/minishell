/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/12/15 10:42:49 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static t_builtin	builtin_type(char *cmd)
{
	if (!cmd)
		return (NOT_BUILTIN);
	return (NOT_BUILTIN
		+ CD_BUILTIN * (cmd[0] == 'c' && cmd[1] == 'd' && !cmd[2])
		+ ECHO_BUILTIN * (cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h'
			&& cmd[3] == 'o' && !cmd[4])
		+ ENV_BUILTIN * (cmd[0] == 'e' && cmd[1] == 'n' && cmd[2] == 'v'
			&& !cmd[3])
		+ EXIT_BUILTIN * (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i'
			&& cmd[3] == 't' && !cmd[4])
		+ EXPORT_BUILTIN * (cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'p'
			&& cmd[3] == 'o' && cmd[4] == 'r' && cmd[5] == 't' && !cmd[6])
		+ PWD_BUILTIN * (cmd[0] == 'p' && cmd[1] == 'w' && cmd[2] == 'd'
			&& !cmd[3])
		+ UNSET_BUILTIN * (cmd[0] == 'u' && cmd[1] == 'n' && cmd[2] == 's'
			&& cmd[3] == 'e' && cmd[4] == 't' && !cmd[5]));
}

static bool	get_cmd(t_cmd *cmd, char **line, t_env *env)
{
	t_cmd_parsing	cmdp;

	init_cmd_parsing(&cmdp, *line);
	cmdp.cmd = cmd;
	if (get_argv_redirv(&cmdp, env))
		return (false);
	while (!is_end_of_cmd(&cmdp))
	{
		if (!cmdp.in_expand && (*(cmdp.str) == '>' || *(cmdp.str) == '<'))
		{
			if (cmdp.curr_redir->type == AMBI_REDIR)
				go_to_end_of_redir(&cmdp, env);
			else if (get_redir(&cmdp, env))
				return (true);
		}
		else if (*(cmdp.str) != ' ')
		{
			if (get_arg(&cmdp, env))
				return (true);
		}
		else
			cmdp.str++;
		if (is_end_of_expand(&cmdp))
			exit_expand(&cmdp);
	}
	cmdp.cmd->builtin = builtin_type(*(cmdp.cmd->argv));
	*line = cmdp.str;
	return (false);
}

static inline void	set_op(t_shell_op *shell_op, char **line)
{
	skip_spaces(line);
	shell_op->op_type += PIPE_OP * (**line == '|' && *(*line + 1) != '|')
		+ AND_OP * (**line == '&')
		+ OR_OP * (**line == '|' && *(*line + 1) == '|');
	*line += !is_end_of_subshell(*line)
		+ (shell_op->op_type == AND_OP || shell_op->op_type == OR_OP);
}

static inline bool	increment_subshell_op(t_shell_op **subshell_op, char *line,
	t_env *env)
{
	if (!is_end_of_subshell(line) 
		&& safe_shell_op_alloc(&(*subshell_op)->next, env))
		return (true);
	*subshell_op = (*subshell_op)->next;
	return (false);
}

static inline bool	get_subshell_op(char **line, t_shell_op *subshell_op,
	t_env *env)
{
	while (!is_end_of_subshell(*line))
	{
		if (**line != ' ')
		{
			if (**line == '(')
			{
				if (safe_shell_op_alloc((t_shell_op **) &subshell_op->op, env))
					return (true);
				(*line)++;
				subshell_op->is_subshell = true;
				if (get_subshell_op(line, subshell_op->op, env))
					return (true);
			}
			else if (safe_cmd_alloc((t_cmd **) &subshell_op->op, env)
					|| get_cmd(subshell_op->op, line, env))
					return (true);
			set_op(subshell_op, line);
			if (increment_subshell_op(&subshell_op, *line, env))
				return (true);
		}
		else
			(*line)++;
	}
	(*line) += (**line == ')');
	return (false);
}

bool	get_shell_op_line(char **line, t_shell_op **shell_op, t_env *env)
{
	// char	*tmp_line;

	// tmp_line = *line;
	if (/*check_line_parsing(&tmp_line, env)
		||*/ safe_shell_op_alloc(shell_op, env))
		return (true);
	return (get_subshell_op(line, *shell_op, env));
}
