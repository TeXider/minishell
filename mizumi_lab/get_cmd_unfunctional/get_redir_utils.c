/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:44:04 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 11:36:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	open_redir(char *name, t_type type, t_rdir status, t_env *env)
{
	int	fd;

	if (type == HDOC)
		return (open_hdoc(name, status, env));
	fd = open(name, O_RDONLY * (type == IN) | O_WRONLY * (type >= OUT)
			| O_APPEND * (type == APPND) | O_CREAT * (type >= OUT));
	if (fd == -1)
		return (create_error(name, CLOSE_ERR, env));
	return (fd);
}

inline bool	close_prev_redir(t_cmd *cmd, t_type type, t_env *env)
{
	if (close(cmd->fd_in * (type <= IN) + cmd->fd_out * (type >= OUT)))
		return (create_error(NULL, CLOSE_ERR, env));
}

inline bool	handle_redir_err(char *redir, t_err status, t_env *env)
{
	if (status == AMBI_REDIR_ERR)
		return (create_error(redir, AMBI_REDIR_ERR, env));
	if (status == SYS_ERR)
		return (true);
}