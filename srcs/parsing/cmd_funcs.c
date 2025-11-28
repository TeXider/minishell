/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:15:58 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:51:58 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	set_new_cmd(t_cmd *cmd, t_env *env)
{
	cmd->path = NULL;
	cmd->cmd_name_is_path = false;
	cmd->argv = NULL;
	cmd->redirv = NULL;
	cmd->redirv_len = 0;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
	cmd->fd_in_type = STD;
	cmd->fd_out_type = STD;
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd->argv && cmd->fd_in == 0 && cmd->fd_out == 1);
}
