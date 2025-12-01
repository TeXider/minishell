/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:59:03 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 11:56:00 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void free_cmd_list(t_cmd *cmd_list, size_t len)
{
	t_cmd	*cmd;
	size_t	i;

	while (--len != (size_t)(-1))
	{
		cmd = cmd_list + len;
		if (cmd->argv && *(cmd->argv) != cmd->path)
			safe_free(cmd->path);
		i = -1;
		while (cmd->argv && cmd->argv[++i])
			free(cmd->argv[i]);
		safe_free(cmd->argv);
		while (cmd->redirv && --(cmd->redirv_len))
			safe_free(cmd->redirv[cmd->redirv_len].name);
		safe_free(cmd->redirv);
		safe_close(cmd->fd_in);
		safe_close(cmd->fd_out);
	}
}

static inline void	wait_children(t_env *env)
{
	pid_t	wait_pid;
	int		status;

	wait_pid = wait(&status);
	while (wait_pid != -1)
	{
		if (!env->exit_code)
			set_exit_code((wait_pid == env->last_pid)
				* (WIFEXITED(status) * WEXITSTATUS(status)
				+ WIFSIGNALED(status) * (128 + WTERMSIG(status))), env);
		wait_pid = wait(&status);
	}
}

void	raboushell(char *input, t_env *env)
{
	t_cmd	*cmd_list;
	size_t	cmd_list_len;

	cmd_list = NULL;
	if (!get_cmd_line(input, &cmd_list, &cmd_list_len, env))
	{
		exec_cmd_line(cmd_list, cmd_list_len, env);
		wait_children(env);
	}
	if (cmd_list && cmd_list_len)
		free_cmd_list(cmd_list, cmd_list_len);
}
