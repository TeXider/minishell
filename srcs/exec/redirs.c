/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:54:07 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 13:26:53 by almighty         ###   ########.fr       */
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
		throw_error(env);
		return (true);
	}
	return (false);
}

static inline bool	set_cmd_fds(t_cmd *cmd, size_t redir_i, t_env *env)
{
	if (!cmd->is_fd_in_hdoc && cmd->redirv[redir_i].type == IN)
	{
		safe_close(&cmd->fd_in, FD_NULL);
		if (open_redir(cmd->redirv[redir_i].name, &cmd->fd_in,
				cmd->redirv[redir_i].type, env))
			return (true);
	}
	else if (cmd->redirv[redir_i].type == OUT
		|| cmd->redirv[redir_i].type == APPND)
	{
		safe_close(&cmd->fd_out, FD_NULL);
		if (open_redir(cmd->redirv[redir_i].name, &cmd->fd_out,
				cmd->redirv[redir_i].type, env))
			return (true);
	}
	return (false);
}

bool	open_cmd_redirs(t_cmd *cmd, t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < cmd->redirv_len)
	{
		if (cmd->redirv[i].type == AMBI_REDIR)
		{
			create_error(cmd->redirv[i].name, AMBI_REDIR_ERR, env);
			throw_error(env);
			return (true);
		}
		if (set_cmd_fds(cmd, i, env))
			return (true);
	}
	return (false);
}

bool	set_redirs_to_std(t_cmd *cmd, t_exec *exec, t_env *env)
{
	int	fd_in;
	int	fd_out;

	fd_in = (cmd->fd_in - *exec->pipe_fd_read) * (cmd->fd_in != FD_NULL)
		+ *exec->pipe_fd_read;
	fd_out = (cmd->fd_out - *exec->pipe_fd_write) * (cmd->fd_out != FD_NULL)
		+ *exec->pipe_fd_write;
	printf("%s: fd_in %d; fd_out %d\n", cmd->argv[0], fd_in, fd_out);
	return (dup2_std((cmd->fd_in - *exec->pipe_fd_read) * (cmd->fd_in != FD_NULL)
		+ *exec->pipe_fd_read,
		(cmd->fd_out - *exec->pipe_fd_write) * (cmd->fd_out != FD_NULL)
		+ *exec->pipe_fd_write, env));
}
