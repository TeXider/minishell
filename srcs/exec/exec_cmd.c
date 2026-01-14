/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:34:10 by almighty          #+#    #+#             */
/*   Updated: 2026/01/14 13:01:34 by almighty         ###   ########.fr       */
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

void	exec_cmd(t_cmd *cmd, t_exec *exec, t_env *env)
{
	if (!*(cmd->argv) && !cmd->redirv[0].name)
		set_exit_code(0, env);
	else if (!open_cmd_redirs(cmd, env))
	{
		write(1, "exit\n", 6 * (cmd->builtin == EXIT_BUILTIN && !env->in_fork));
		if (!set_redirs_to_std(cmd, exec, env))
		{
			if (cmd->builtin)
				exec_builtin(cmd, env);
			else if (!handle_fork(exec, env)
				&& exec->is_child
				&& *(cmd->argv)
				&& !get_path(cmd, env))
			{
				close_pipes(exec);
				safe_close(&cmd->fd_in, FD_NULL);
				safe_close(&cmd->fd_out, FD_NULL);
				execve(cmd->path, cmd->argv, env->envp);
				create_error("execve()", SYS_ERR, env);
			}
		}
	}
	safe_close(&cmd->fd_in, FD_NULL);
	safe_close(&cmd->fd_out, FD_NULL);
}
