/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:54:07 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 18:30:19 by almighty         ###   ########.fr       */
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
		create_error(name, SYS_ERR, env);
		return (true);
	}
	return (false);
}

static inline bool	set_cmd_fds(t_cmd *cmd, size_t redir_i, t_env *env)
{
	if (cmd->fd_in_type != HDOC && cmd->redirv[redir_i].type == IN)
	{
		safe_close(&cmd->fd_in, STD_IN);
		if (open_redir(cmd->redirv[redir_i].name, &cmd->fd_in,
				cmd->redirv[redir_i].type, env))
			return (true);
	}
	else if (cmd->redirv[redir_i].type >= OUT)
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

	if (env->saved_std_in == FD_NULL && env->saved_std_out == FD_NULL
		&& (safe_dup(STD_IN, &env->saved_std_in, env)
			|| safe_dup(STD_OUT, &env->saved_std_out, env)))
			return (true);
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

void	reset_redirs(t_cmd *cmd_list, size_t cmd_list_i, t_env *env)
{
	if (cmd_list_i > 0)
	{
		safe_close(&cmd_list[cmd_list_i - 1].fd_in, FD_NULL);
		safe_close(&cmd_list[cmd_list_i - 1].fd_out, FD_NULL);
	}
	dup2_std(env->saved_std_in, env->saved_std_out, env);
}
