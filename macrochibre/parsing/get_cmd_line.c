/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/27 10:46:41 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_builtin	builtin_type(char *cmd)
{
	if (!(cmd))
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

static bool	get_cmd(t_cmd_parsing *cmdp, t_env *env)
{
	if (get_argv_redirv(cmdp, env))
		return (false);
	while (!is_end_of_cmd(cmdp))
	{
		if (!cmdp->in_expand && (*(cmdp->str) == '>' || *(cmdp->str) == '<'))
		{
			if (cmdp->curr_redir->type == AMBI_REDIR)
				go_to_end_of_redir(cmdp, env);
			else if (get_redir(cmdp, env))
				return (true);
		}
		else if (*(cmdp->str) != ' ')
		{
			if (get_arg(cmdp, env))
				return (true);
		}
		else
			cmdp->str++;
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	cmdp->cmd->argv = builtin_type(*(cmdp->cmd->argv));
	return (false);
}

static bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	bool			is_empty;
	bool			has_cmd;

	init_cmd_parsing(&tmp_cmdp, line);
	has_cmd = false;
	while (*(tmp_cmdp.str) && *(tmp_cmdp.str) != '\n')
	{
		is_empty = true;
		if (go_to_end_of_cmd(&tmp_cmdp, cmd_list_len, &is_empty, env))
			return (true);
		has_cmd |= !is_empty;
		if (has_cmd && is_empty)
		{
			create_error(tmp_cmdp.str, UNEXPECTED_TOKEN_ERR, env);
			return (true);
		}
		tmp_cmdp.str += (*(tmp_cmdp.str) == '|');
	}
	if (has_cmd && (is_empty || (*(tmp_cmdp.str - 1) == '|')))
	{
		create_error(tmp_cmdp.str, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (false);
}

bool	get_cmd_line(char *line, t_cmd **cmd_list, size_t *cmd_list_len,
	t_env *env)
{
	t_cmd_parsing	cmdp;
	size_t			cmd_list_index;

	*cmd_list_len = 0;
	if (check_line_parsing(line, cmd_list_len, env))
		return (true);
	if (!*cmd_list_len)
		return (false);
	if (safe_malloc((void **) cmd_list, sizeof(t_cmd) * (*cmd_list_len), env))
		return (true);
	init_cmd_parsing(&cmdp, line);
	cmd_list_index = 0;
	while (*(cmdp.str) && *(cmdp.str) != '\n')
	{
		set_new_cmd(*cmd_list + cmd_list_index, env);
		reset_cmd_parsing(&cmdp, *cmd_list + cmd_list_index);
		if (get_cmd(&cmdp, env))
			return (true);
		cmdp.str += (*(cmdp.str) == '|');
		cmd_list_index++;
	}
	return (false);
}
