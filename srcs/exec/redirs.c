/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:54:07 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 15:10:07 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

static inline bool	open_redir(char *name, int *fd, t_rtype type, t_env *env)
{
	*fd = open(name, O_RDONLY * (type == IN)
			| (O_WRONLY * (type >= OUT) + READ * (type == APPND))
			| O_APPEND * (type == APPND)
			| O_CREAT * (type >= OUT)
			| O_TRUNC * (type == OUT), 0664);
	if (*fd == -1)
	{
		create_error(name, FILE_ERR, env);
		return (true);
	}
	return (false);
}

static inline bool	set_cmd_fds(t_cmd *cmd, size_t redir_i, t_env *env)
{
	if (!cmd->is_fd_in_hdoc && cmd->redirv[redir_i].type == IN)
	{
		safe_close(&cmd->fd_in, STD_IN);
		if (open_redir(cmd->redirv[redir_i].name, &cmd->fd_in,
				cmd->redirv[redir_i].type, env))
			return (true);
	}
	else if (cmd->redirv[redir_i].type == OUT
		|| cmd->redirv[redir_i].type == APPND)
	{
		safe_close(&cmd->fd_out, STD_OUT);
		if (open_redir(cmd->redirv[redir_i].name, &cmd->fd_out,
				cmd->redirv[redir_i].type, env))
			return (true);
	}
	return (false);
}

bool	set_redirs(t_cmd *cmd, t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < cmd->redirv_len)
	{
		if (cmd->redirv[i].type == AMBI_REDIR)
		{
			create_error(cmd->redirv[i].name, AMBI_REDIR_ERR, env);
			return (true);
		}
		if (set_cmd_fds(cmd, i, env))
			return (true);
	}
	return (false);
}

void	close_redirs(t_cmd *cmd_list, size_t cmd_list_i, t_env *env)
{
	if (cmd_list_i > 0)
	{
		safe_close(&cmd_list[cmd_list_i - 1].fd_in, FD_NULL);
		safe_close(&cmd_list[cmd_list_i - 1].fd_out, FD_NULL);
	}
	safe_close(&cmd_list[cmd_list_i].fd_in, FD_NULL);
	safe_close(&cmd_list[cmd_list_i].fd_out, FD_NULL);
	safe_close(&env->discarded_pipe_fd, FD_NULL);
}

void	reset_redirs(t_cmd *cmd_list, size_t cmd_list_i, t_env *env)
{
	close_redirs(cmd_list, cmd_list_i, env);
	dup2_std(env->saved_std_in, env->saved_std_out, env);
}
