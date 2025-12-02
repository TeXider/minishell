/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:06:30 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 18:21:08 by almighty         ###   ########.fr       */
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
		cmd->fd_out += (pipe_fds[STD_OUT] - STD_OUT)
			* (cmd->fd_out_type == STD);
		next_cmd->fd_in += (pipe_fds[STD_IN] - STD_IN)
			* (next_cmd->fd_in_type == STD);
		cmd->fd_out_type += (PIPE - STD) * (cmd->fd_out_type == STD);
		next_cmd->fd_in_type += (PIPE - STD) * (next_cmd->fd_in_type == STD);
	}
	return (false);
}
