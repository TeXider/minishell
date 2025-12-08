/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:06:30 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 15:09:47 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

bool	handle_pipes(t_cmd *cmd, t_cmd *next_cmd, t_env *env)
{
	int	pipe_fds[2];

	if (cmd != next_cmd)
	{
		if (pipe(pipe_fds))
		{
			create_error("pipe()", SYS_ERR, env);
			return (true);
		}
		cmd->fd_out = pipe_fds[STD_OUT];
		if (!next_cmd->is_fd_in_hdoc)
			next_cmd->fd_in = pipe_fds[STD_IN];
		else
			env->discarded_pipe_fd = pipe_fds[STD_IN];
	}
	return (false);
}
