/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:06:30 by almighty          #+#    #+#             */
/*   Updated: 2025/11/14 10:37:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline void	init_pipes(t_pipes *pipes)
{
	pipes->pipe_fds[P_READ] = STD_IN;
	pipes->pipe_fds[P_WRITE] = STD_OUT;
	pipes->next_pipe_fds[P_READ] = STD_IN;
	pipes->next_pipe_fds[P_WRITE] = STD_OUT;
	pipes->fd_read = STD_IN;
	pipes->fd_write = STD_OUT;
	pipes->is_next_pipe = false;
}

inline bool	repipe(int pipe_fds[2], bool is_last_cmd, t_env *env)
{
	safe_close(pipe_fds + P_READ, STD_IN);
	safe_close(pipe_fds + P_WRITE, STD_OUT);
	if (!is_last_cmd && pipe(pipe_fds))
	{
		create_error("pipe()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

inline void	close_pipes(t_pipes *pipes)
{
	safe_close(pipes->pipe_fds + P_READ, FD_NULL);
	safe_close(pipes->pipe_fds + P_WRITE, FD_NULL);
	safe_close(pipes->next_pipe_fds + P_READ, FD_NULL);
	safe_close(pipes->next_pipe_fds + P_WRITE, FD_NULL);
}

inline bool	handle_pipes(t_pipes *pipes, size_t cmd_list_i, size_t cmd_list_len,
	t_env *env)
{
	if (cmd_list_len == 1)
		return (false);
	if (!pipes->is_next_pipe)
	{
		if (repipe(pipes->pipe_fds, (cmd_list_i + 1 == cmd_list_len), env))
			return (true);
		pipes->fd_write = pipes->pipe_fds[P_WRITE];
		pipes->fd_read = pipes->next_pipe_fds[P_READ];
	}
	else
	{
		if (repipe(pipes->next_pipe_fds, (cmd_list_i + 1 == cmd_list_len), env))
			return (true);
		pipes->fd_write = pipes->next_pipe_fds[P_WRITE];
		pipes->fd_read = pipes->pipe_fds[P_READ];
	}
	return (false);
}
