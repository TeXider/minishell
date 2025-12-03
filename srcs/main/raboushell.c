/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:59:03 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 08:17:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void	free_redirs(t_cmd *cmd)
{
	if (cmd->redirv_len)
	{
		while (--(cmd->redirv_len) != (size_t)(-1))
		{
			safe_free((void **) &cmd->redirv[cmd->redirv_len].name);
			if (cmd->redirv[cmd->redirv_len].type == AMBI_REDIR)
				break ;
		}
	}
	safe_free((void **) &cmd->redirv);
}

static inline void	free_cmd_list(t_cmd *cmd_list, size_t len)
{
	t_cmd	*cmd;
	size_t	i;

	if (cmd_list && len)
	{
		while (--len != (size_t)(-1))
		{
			cmd = cmd_list + len;
			if (cmd->argv && *(cmd->argv) != cmd->path)
				safe_free((void **) &cmd->path);
			i = -1;
			while (cmd->argv && cmd->argv[++i])
				free(cmd->argv[i]);
			safe_free((void **) &cmd->argv);
			free_redirs(cmd);
			safe_close(&cmd->fd_in, FD_NULL);
			safe_close(&cmd->fd_out, FD_NULL);
		}
	}
	safe_free((void **) &cmd_list);
}

static inline void	wait_children(t_env *env)
{
	pid_t	wait_pid;
	int		status;

	wait_pid = 0;
	while (wait_pid > -1 && --env->children_count >= 0)
	{
		wait_pid = wait(&status);
		if (!env->exit_code && env->last_pid != -1 && wait_pid == env->last_pid)
			set_exit_code((WIFEXITED(status) * WEXITSTATUS(status)
							+ WIFSIGNALED(status) * (128 + WTERMSIG(status))),
							env);
	}
	if (wait_pid == -1)
		create_error("wait()", SYS_ERR, env);
}

void	raboushell(char *input, t_env *env)
{
	t_cmd	*cmd_list;
	size_t	cmd_list_len;

	cmd_list = NULL;
	if (!get_cmd_line(input, &cmd_list, &cmd_list_len, env))
	{
		env->children_count = 0;
		exec_cmd_line(cmd_list, cmd_list_len, env);
		if (!env->in_fork)
			wait_children(env);
	}
	free_cmd_list(cmd_list, cmd_list_len);
}
