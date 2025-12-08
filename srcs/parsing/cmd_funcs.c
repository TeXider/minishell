/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:15:58 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 15:06:53 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	set_new_cmd(t_cmd *cmd, t_env *env)
{
	(void) env;
	cmd->path = NULL;
	cmd->cmd_name_is_path = false;
	cmd->argv = NULL;
	cmd->redirv = NULL;
	cmd->redirv_len = 0;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
	cmd->is_fd_in_hdoc = false;
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd->argv && cmd->fd_in == 0 && cmd->fd_out == 1);
}
