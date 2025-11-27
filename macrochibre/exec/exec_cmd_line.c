/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:54:12 by almighty          #+#    #+#             */
/*   Updated: 2025/11/27 10:25:37 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	exec_cmd(t_cmd *cmd, t_pipes *pipes, t_env *env)
{
	if (dup2(cmd->fd_in, STD_IN) == -1
		|| dup2(cmd->fd_out, STD_OUT) == -1)
	{
		create_error("dup2()", SYS_ERR, env);
		return ;
	}
	if (cmd->fd_in_type != PIPE)
		safe_close(&cmd->fd_in, FD_NULL);
	if (cmd->fd_out_type != PIPE)
		safe_close(&cmd->fd_out, FD_NULL);
	close_pipes(pipes);
	if (cmd->is_builtin)
		exec_builtin(cmd, env);
	else
	{
		execve(cmd->path, cmd->argv, env->envp);
		create_error("execve()", SYS_ERR, env);
	}
}
//add if is_builtin() exec_builtin(); else execve()

static inline bool	handle_fork(t_cmd *cmd, pid_t *pid, t_pipes *pipes,
	t_env *env)
{
	*pid = fork();
	if (*pid == -1)
	{
		create_error("fork()", SYS_ERR, env);
		return (true);
	}
	if (!*pid)
	{
		env->in_fork = true;
		if (open_redirs(cmd, env)
			|| (!cmd->is_builtin && get_path(cmd, env)))
			return (true);
		cmd->fd_in += (pipes->fd_read - cmd->fd_in) * (cmd->fd_in == STD_IN);
		cmd->fd_in_type = (PIPE - STD) * (cmd->fd_in_type == STD)
			+ cmd->fd_in_type;
		cmd->fd_out += (pipes->fd_write - cmd->fd_out)
			* (cmd->fd_out == STD_OUT);
		cmd->fd_out_type = (PIPE - STD) * (cmd->fd_in_type == STD)
			+ cmd->fd_in_type;
		exec_cmd(cmd, pipes, env);
		close_pipes(pipes);
		return (true);
	}
	return (false);
}

bool	exec_cmd_line(t_cmd *cmd_list, size_t cmd_list_len, t_env *env)
{
	t_pipes	pipes;
	pid_t	pid;
	size_t	i;

	if (cmd_list_len == 1 && (*cmd_list).is_builtin)
		return (exec_builtin(*cmd_list, env));
	init_pipes(&pipes);
	i = -1;
	while (++i < cmd_list_len)
	{
		if (handle_pipes(&pipes, i, cmd_list_len, env)
			|| handle_fork(cmd_list + i, &pid, &pipes, env))
			return (true);
		pipes.is_next_pipe = !pipes.is_next_pipe;
	}
	close_pipes(&pipes);
	env->last_pid = pid;
	return (false);
}
//	i = -1;
//	while (++i < cmd_list_len)
//		wait(NULL);
// put the wait in exec_cmd_line caller, therefore whether
// there was an error or not, every child is waited for.