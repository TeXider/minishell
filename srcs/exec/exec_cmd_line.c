/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:54:12 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 21:50:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "../includes/builtins.h"

static inline void	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (cmd->builtin == CD_BUILTIN)
		builtin_cd(cmd->argv + 1, env);
	else if (cmd->builtin == EXIT_BUILTIN)
		builtin_exit(cmd->argv + 1, env);
	else if (cmd->builtin == EXPORT_BUILTIN)
		builtin_export(cmd->argv + 1, env);
	else if (cmd->builtin == PWD_BUILTIN)
		builtin_pwd(env);
	else if (cmd->builtin == UNSET_BUILTIN)
		builtin_unset(cmd->argv + 1, env);
	else if (cmd->builtin == ECHO_BUILTIN)
		builtin_echo(cmd->argv + 1);
	else if (cmd->builtin == ENV_BUILTIN)
		builtin_env(env);
}

static inline void	exec_cmd(t_cmd *cmd, pid_t *pid, t_env *env)
{
	*pid = fork();
	if (*pid == -1)
		create_error("fork()", SYS_ERR, env);
	else if (!*pid)
	{
		env->in_fork = true;
		if (!cmd->builtin && get_path(cmd, env))
			return ;
		safe_close(&cmd->fd_in, FD_NULL);
		safe_close(&cmd->fd_out, FD_NULL);
		if (cmd->builtin)
			exec_builtin(cmd, env);
		else
		{
			execve(cmd->path, cmd->argv, env->envp);
			create_error("execve()", SYS_ERR, env);
		}
	}
	env->children_count += (*pid != -1);
}

static inline void	exec_single_builtin(t_cmd *cmd, t_env *env)
{
	if (!set_redirs(cmd, env)
		&& !dup2_std(cmd->fd_in, cmd->fd_out, env))
		exec_builtin(cmd, env);
	safe_close(&cmd->fd_in, FD_NULL);
	safe_close(&cmd->fd_out, FD_NULL);
	dup2_std(env->saved_std_in, env->saved_std_out, env);
}

void	exec_cmd_line(t_cmd *cmd_list, size_t cmd_list_len, t_env *env)
{
	pid_t	pid;
	size_t	i;

	pid = -1;
	if (cmd_list_len == 1 && cmd_list->builtin)
		exec_single_builtin(cmd_list, env);
	else
	{
		i = -1;
		while (++i < cmd_list_len && !env->in_fork && env->err != SYS_ERR)
		{
			if (!set_redirs(cmd_list + i, env)
				&& !handle_pipes(cmd_list + i, cmd_list + i
					+ (i + 1 != cmd_list_len), env)
				&& *(cmd_list[i].argv)
				&& !dup2_std(cmd_list[i].fd_in, cmd_list[i].fd_out, env))
			{
				if (i > 0)
					safe_close(&cmd_list[i - 1].fd_out, FD_NULL);
				exec_cmd(cmd_list + i, &pid, env);
			}
			reset_redirs(cmd_list, i, env);
		}
		env->last_pid = pid;
	}
}
