/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:54:12 by almighty          #+#    #+#             */
/*   Updated: 2025/11/03 10:42:16 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	exec_cmd(t_cmd *cmd, t_pipes *pipes, t_env *env)
{
	if (dup2(cmd->fd_in, STD_IN) == -1 || dup2(cmd->fd_out, STD_OUT) == -1)
	{
		create_error("dup2()", SYS_ERR, env);
		return ;
	}
	if (!cmd->is_fd_in_pipe)
		safe_close(&cmd->fd_in);
	if (!cmd->is_fd_out_pipe)
		safe_close(&cmd->fd_out);
	close_pipes(pipes);
	execve(cmd->argv[0], cmd->argv, env->envp);
	create_error("execve()", SYS_ERR, env);
}
//add if is_builtin() exec_builtin(); else execve()

static inline bool	handle_fork(pid_t *pid, t_pipes *pipes, char *line,
	t_env *env)
{
	t_cmd	cmd;

	*pid = fork();
	if (*pid == -1)
	{
		create_error("fork()", SYS_ERR, env);
		return (true);
	}
	if (!*pid)
	{
		set_new_cmd(&cmd, env);
		cmd.fd_in = pipes->fd_read;
		cmd.is_fd_in_pipe = true;
		cmd.fd_out = pipes->fd_write;
		cmd.is_fd_out_pipe = true;
		if (!get_cmd(&line, &cmd, env) && !get_path(&cmd, env))
			exec_cmd(&cmd, pipes, env);
		close_pipes(pipes);
		free_data(&cmd, line, env);
		throw_error(env);
		exit(0);
	}
	return (false);
}

static inline bool	handle_pipes(t_pipes *pipes, bool is_last_cmd, t_env *env)
{
	if (!pipes->is_next_pipe)
	{
		if (repipe(pipes->pipe_fds, is_last_cmd, env))
			return (true);
		pipes->fd_write = pipes->pipe_fds[P_WRITE];
		pipes->fd_read = pipes->next_pipe_fds[P_READ];
	}
	else
	{
		if (repipe(pipes->next_pipe_fds, is_last_cmd, env))
			return (true);
		pipes->fd_write = pipes->next_pipe_fds[P_WRITE];
		pipes->fd_read = pipes->pipe_fds[P_READ];
	}
	return (false);
}

bool	exec_cmd_line(char **line, t_cmd *cmd_list, size_t cmd_list_len,
	t_env *env)
{
	t_pipes	pipes;
	pid_t	pid;
	size_t	i;

	init_pipes(&pipes);
	i = -1;
	while (++i < cmd_list_len)
	{
		if ((cmd_list_len > 1
				&& handle_pipes(&pipes, i == cmd_list_len - 1, env))
			|| handle_fork(&pid, &pipes, *line, env))
			return (true);
		*line = cmd_list[i].start_ptr;
		pipes.is_next_pipe = !pipes.is_next_pipe;
	}
	close_pipes(&pipes);
	env->last_pid = pid;
	i = -1;
	while (++i < cmd_list_len)
		wait(NULL);
	return (false);
}
// put the wait in exec_cmd_line caller, therefore whether
// there was an error or not, every child is waited for.