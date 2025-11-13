/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/13 16:06:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!cmd_list_len)
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
