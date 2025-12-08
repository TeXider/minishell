/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:54:12 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 14:55:37 by tpanou-d         ###   ########.fr       */
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
	if (!env->err && cmd->builtin != EXIT_BUILTIN)
		set_exit_code(0, env);
}

static inline void	exec_cmd(t_cmd *cmd_list, size_t cmd_list_i,
	pid_t *pid, t_env *env)
{
	t_cmd	*cmd;

	*pid = fork();
	if (*pid == -1)
		create_error("fork()", SYS_ERR, env);
	else if (!*pid)
	{
		env->in_fork = true;
		cmd = cmd_list + cmd_list_i;
		if (!set_redirs(cmd, env) && *(cmd->argv)
			&& !dup2_std(cmd->fd_in, cmd->fd_out, env))
		{
			if (!cmd->builtin && get_path(cmd, env))
				return ;
			if (cmd->builtin)
				exec_builtin(cmd, env);
			else
			{
				close_redirs(cmd_list, cmd_list_i, env);
				execve(cmd->path, cmd->argv, env->envp);
				create_error("execve()", SYS_ERR, env);
			}
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

	if (save_std_fds(env))
		return ;
	env->last_pid = -1;
	if (cmd_list_len == 1 && cmd_list->builtin)
		exec_single_builtin(cmd_list, env);
	else
	{
		i = -1;
		while (!is_end_of_exec(++i, cmd_list_len, env))
		{
			if (!handle_pipes(cmd_list + i, cmd_list + i
					+ (i + 1 != cmd_list_len), env))
				exec_cmd(cmd_list, i, &pid, env);
			reset_redirs(cmd_list, i, env);
		}
		env->last_pid = pid;
	}
}
