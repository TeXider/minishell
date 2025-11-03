/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:06:30 by almighty          #+#    #+#             */
/*   Updated: 2025/11/03 08:54:20 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	safe_close(int *fd)
{
	if (*fd != STD_IN && *fd != STD_OUT && *fd != FD_ERR && *fd != FD_NULL)
	{
		close(*fd);
		*fd = FD_NULL;
	}
}

inline void	close_pipes(t_pipes *pipes)
{
	safe_close(pipes->pipe_fds + P_READ);
	safe_close(pipes->pipe_fds + P_WRITE);
	safe_close(pipes->next_pipe_fds + P_READ);
	safe_close(pipes->next_pipe_fds + P_WRITE);
}

inline bool	repipe(int pipe_fds[2], bool is_final_cmd, t_env *env)
{	
	safe_close(pipe_fds + P_READ);
	safe_close(pipe_fds + P_WRITE);
	if (is_final_cmd)
	{
		pipe_fds[P_READ] = STD_IN;
		pipe_fds[P_WRITE] = STD_OUT;
	}
	else
	{
		if (pipe(pipe_fds))
		{
			create_error("pipe()", SYS_ERR, env);
			return (true);
		}
	}
	return (false);
}

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
