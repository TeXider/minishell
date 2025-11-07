/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 08:19:55 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	get_cmd(t_cmd_parsing *cmdp, t_env *env)
{
	size_t	arg_i;

	if (get_argv_redirv(cmdp, env))
		return (false);
	arg_i = 0;
	while (!is_end_of_cmd(*(cmdp->str)))
	{
		if (!cmdp->cmd->start_ptr && cmdp->str != ' ')
			cmdp->cmd->start_ptr = cmdp->str;
		if (*(cmdp->str) == '>' || *(cmdp->str) == '<')
		{
			if (get_redir(cmdp, env))
				return (true);
		}
		else if (*(cmdp->str) != ' ')
		{
			if (get_arg(cmdp, &arg_i, env))
				return (true);
		}
		else
			cmdp->str++;
	}
	return (false);
}

static bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;

	tmp_cmdp.str = line;
	while (*(tmp_cmdp.str) && *(tmp_cmdp.str) != '\n')
	{
		if (go_to_end_of_cmd(&tmp_cmdp, cmd_list_len, *cmd_list_len, env))
			return (true);
		tmp_cmdp.str += (*(tmp_cmdp.str) == '|');
	}
	return (false);
}

bool	get_cmd_line(char *line, t_cmd **cmd_list, t_env *env)
{
	t_cmd_parsing	cmdp;
	size_t			cmd_list_len;
	size_t			cmd_list_index;

	if (check_line_parsing(line, &cmd_list_len, env))
		return (true);
	if (!cmd_list_len)
		return (false);
	if (safe_cmdlalloc(cmd_list, cmd_list_len, env))
		return (true);
	cmdp.str = line;
	cmd_list_index = 0;
	while (*(cmdp.str) && *(cmdp.str) != '\n')
	{
		set_new_cmd(*cmd_list + cmd_list_index, env);
		cmdp.argv_len = 0;
		cmdp.redirv_len = 0;
		cmdp.cmd = *cmd_list + cmd_list_index;
		if (get_cmd(&cmdp, env))
			return (true);
		cmdp.str += (*(cmdp.str) == '|');
		cmd_list_index++;
	}
	return (false);
}
