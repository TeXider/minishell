/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:24:19 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 13:31:58 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

inline void	close_pipes(t_exec *exec)
{
	safe_close(exec->pipe_fds[0] + P_READ, STD_IN);
	safe_close(exec->pipe_fds[0] + P_WRITE, STD_OUT);
	safe_close(exec->pipe_fds[1] + P_READ, STD_IN);
	safe_close(exec->pipe_fds[1] + P_WRITE, STD_OUT);
}

inline bool	open_pipe(t_exec *exec, t_env *env)
{
	safe_close(exec->pipe_fds[exec->pipe_index & 1] + P_READ, STD_IN);
	safe_close(exec->pipe_fds[exec->pipe_index & 1] + P_WRITE, STD_OUT);
	if (exec->shell_op->op_type == PIPE_OP
		&& pipe(exec->pipe_fds[exec->pipe_index & 1]) == -1)
	{
		create_error("pipe()", SYS_ERR, env);
		return (true);
	}
	exec->pipe_fd_write = exec->pipe_fds[exec->pipe_index & 1] + P_WRITE;
	exec->pipe_fd_read = exec->pipe_fds[(exec->pipe_index - 1) & 1] + P_READ;
	exec->pipe_index++;
	return (false);
}
