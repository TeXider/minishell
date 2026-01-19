/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_shell_op_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:54:12 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:00 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution_bonus.h"
#include "../includes/builtins_bonus.h"

static void	exec_shell_op(t_exec *exec, t_env *env);

static inline void	exec_subshell_op(t_exec *exec, t_env *env)
{
	if (!handle_fork(exec, env)
		&& exec->is_child)
	{
		exec->prev_op = EMPTY_OP;
		exec->children_count = 0;
		exec->last_pid = -1;
		exec->shell_op = exec->shell_op->op;
		exec->is_child = false;
		exec_shell_op(exec, env);
		exec->is_child = true;
	}
}

static inline void	exec_pipeline(t_exec *exec, t_env *env)
{
	int	saved_children_count;

	saved_children_count = exec->children_count;
	exec->children_count = 0;
	exec->prev_op = PIPE_OP;
	while (exec->prev_op == PIPE_OP && !is_end_of_exec(exec, env))
	{
		if (!open_pipe(exec, env)
			&& !handle_fork(exec, env)
			&& exec->is_child)
		{
			if (exec->shell_op->is_subshell)
				exec_subshell_op(exec, env);
			else
				exec_cmd(exec->shell_op->op, exec, env);
			return ;
		}
		safe_close(exec->pipe_fd_write, STD_OUT);
		exec->prev_op = exec->shell_op->op_type;
		if (exec->shell_op->next)
			exec->shell_op = exec->shell_op->next;
	}
	close_pipes(exec);
	wait_children(exec, env);
	exec->children_count = saved_children_count;
}

static void	exec_shell_op(t_exec *exec, t_env *env)
{
	while (!is_end_of_exec(exec, env))
	{
		if (has_to_exec(exec, env))
		{
			if (exec->shell_op->op_type == PIPE_OP)
				exec_pipeline(exec, env);
			else if (exec->shell_op->is_subshell)
				exec_subshell_op(exec, env);
			else
				exec_cmd(exec->shell_op->op, exec, env);
			if (exec->is_child)
				return ;
			wait_children(exec, env);
			exec->prev_op = exec->shell_op->op_type;
		}
		exec->shell_op = exec->shell_op->next;
	}
}

void	exec_shell_op_line(t_shell_op *shell_op, t_env *env)
{
	t_exec	exec;

	if (!shell_op->op
		|| save_std_fds(&exec, env))
		return ;
	init_exec(&exec, shell_op);
	exec_shell_op(&exec, env);
	close_pipes(&exec);
	dup2_std(exec.saved_std_in, exec.saved_std_out, env);
	close(exec.saved_std_in);
	close(exec.saved_std_out);
}
