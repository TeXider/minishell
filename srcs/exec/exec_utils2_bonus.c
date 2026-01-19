/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:28:23 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:05 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution_bonus.h"

inline bool	handle_fork(t_exec *exec, t_env *env)
{
	if (exec->is_child)
		return (false);
	exec->last_pid = fork();
	if (exec->last_pid == -1)
		create_error("fork()", SYS_ERR, env);
	else if (!exec->last_pid)
		exec->is_child = true;
	exec->children_count += (exec->last_pid && exec->last_pid != -1);
	env->in_fork |= !exec->last_pid;
	return (env->err != SUCCESS);
}

inline void	wait_children(t_exec *exec, t_env *env)
{
	pid_t	wait_pid;
	int		status;

	wait_pid = 0;
	while (exec->children_count)
	{
		wait_pid = wait(&status);
		if (wait_pid == -1)
			create_error("wait()", SYS_ERR, env);
		else if (!env->err && wait_pid == exec->last_pid)
			set_exit_code((WIFEXITED(status) * WEXITSTATUS(status)
					+ WIFSIGNALED(status) * (128 + WTERMSIG(status))),
				env);
		exec->children_count--;
	}
}

inline void	init_exec(t_exec *exec, t_shell_op *shell_op)
{
	exec->prev_op = EMPTY_OP;
	exec->shell_op = shell_op;
	exec->children_count = 0;
	exec->last_pid = -1;
	exec->pipe_fds[0][P_READ] = STD_IN;
	exec->pipe_fds[0][P_WRITE] = STD_OUT;
	exec->pipe_fds[1][P_READ] = STD_IN;
	exec->pipe_fds[1][P_WRITE] = STD_OUT;
	exec->pipe_fd_read = exec->pipe_fds[0] + P_READ;
	exec->pipe_fd_write = exec->pipe_fds[0] + P_WRITE;
	exec->pipe_index = 0;
	exec->is_child = false;
}
