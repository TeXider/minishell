/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:00:48 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:24 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

static inline t_builtin	builtin_type(char *cmd)
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

static inline bool	init_get_cmd(t_cmd **cmd, t_cmd_parsing *cmdp, char *line,
	t_env *env)
{
	if (safe_cmd_alloc(cmd, env))
		return (true);
	init_cmd_parsing(cmdp, *cmd, line);
	return (get_argv_redirv(cmdp, env));
}

bool	get_cmd(t_cmd **cmd, char **line, t_env *env)
{
	t_cmd_parsing	cmdp;

	if (init_get_cmd(cmd, &cmdp, *line, env))
		return (true);
	while (!is_end_of_cmd(&cmdp))
	{
		if (!cmdp.in_expand && (*(cmdp.str) == '>' || *(cmdp.str) == '<'))
		{
			if (get_redir(&cmdp, env))
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
	(*cmd)->builtin = builtin_type(*((*cmd)->argv));
	*line = cmdp.str;
	return (false);
}
