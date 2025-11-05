/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:44:04 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 13:46:04 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

inline int	open_redir(char *name, t_rtype type, bool has_quotes, t_env *env)
{
	int	fd;

	if (type == HDOC)
		fd = open_hdoc(name, has_quotes, env);
	else
		fd = open(name, O_RDONLY * (type == IN)
				| (O_WRONLY * (type >= OUT) + READ * (type == APPND))
				| O_APPEND * (type == APPND)
				| O_CREAT * (type >= OUT)
				| O_TRUNC * (type >= OUT && type != APPND), 0664);
	if (fd == -1)
	{
		if ()
			create_error(name, FILE_ERR, env);
		free(name);
	}
	return (fd);
}

inline void	close_prev_redir(t_cmd *cmd, t_rtype type)
{
	if (type <= IN && !cmd->is_fd_in_pipe)
		safe_close(&cmd->fd_in);
	else if (type >= OUT && !cmd->is_fd_out_pipe)
		safe_close(&cmd->fd_out);
}

inline void	safe_close(int *fd)
{
	if (*fd != STD_IN && *fd != STD_OUT && *fd != FD_ERR && *fd != FD_NULL)
	{
		close(*fd);
		*fd = FD_NULL;
	}
}

inline bool	handle_redir_err(char *redir, t_err status, t_env *env)
{
	if (status == AMBI_REDIR_ERR)
		create_error(redir, AMBI_REDIR_ERR, env);
	return (true);
}
