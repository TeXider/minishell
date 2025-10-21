/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:44:04 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 09:22:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	open_redir(char *name, t_type type, bool has_quotes, t_env *env)
{
	int	fd;

	if (type == HDOC)
		return (open_hdoc(name, has_quotes, env));
	fd = open(name, O_RDONLY * (type == IN) | (O_WRONLY * (type >= OUT)
			+ READ * (type == APPND)) | O_APPEND * (type == APPND)
			| O_CREAT * (type >= OUT) | O_TRUNC * (type >= OUT && type != APPND),
			0664);
	if (fd == -1)
	{
		free(name);
		return (-1 * create_error(NULL, FILE_ERR, env));
	}
	return (fd);
}

inline bool	close_prev_redir(t_cmd *cmd, t_type type, t_env *env)
{
	if (type <= IN && cmd->fd_in != 0)
	{
		if (close(cmd->fd_in))
			return (create_error(NULL, CLOSE_ERR, env));
	}
	else if (cmd->fd_out != 1)
	{
		if (close(cmd->fd_out))
			return (create_error(NULL, CLOSE_ERR, env));
	}
	return (false);
}
// cmd->fd_in += (-1 - cmd->fd_in) * (type <= IN);
// cmd->fd_out += (-1 - cmd->fd_in) * (type >= OUT);

inline bool	handle_redir_err(char *redir, t_err status, t_env *env)
{
	if (status == AMBI_REDIR_ERR)
		return (create_error(redir, AMBI_REDIR_ERR, env));
	return (true);
}