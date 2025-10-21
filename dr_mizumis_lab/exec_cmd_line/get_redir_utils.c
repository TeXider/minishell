/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:44:04 by almighty          #+#    #+#             */
/*   Updated: 2025/10/21 18:12:07 by tpanou-d         ###   ########.fr       */
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
			| O_CREAT * (type >= OUT) | O_TRUNC
			* (type >= OUT && type != APPND), 0664);
	if (fd == -1)
	{
		create_error(name, FILE_ERR, env);
		free(name);
		return (create_error(NULL, FILE_ERR, env));
	}
	return (fd);
}

inline void	close_prev_redir(t_cmd *cmd, t_type type)
{
	if (type <= IN && !cmd->is_fd_in_pipe)
		safe_close(&cmd->fd_in);
	else if (type >= OUT && !cmd->is_fd_out_pipe)
		safe_close(&cmd->fd_out);
}

inline bool	handle_redir_err(char *redir, t_err status, t_env *env)
{
	if (status == AMBI_REDIR_ERR)
		return (create_error(redir, AMBI_REDIR_ERR, env));
	return (true);
}