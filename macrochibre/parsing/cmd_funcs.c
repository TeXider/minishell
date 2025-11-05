/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:15:58 by almighty          #+#    #+#             */
/*   Updated: 2025/11/03 10:31:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	set_new_cmd(t_cmd *cmd, t_env *env)
{
	cmd->path = NULL;
	cmd->argv = env->empty_list;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
	cmd->is_fd_in_pipe = false;
	cmd->is_fd_out_pipe = false;
	cmd->is_fd_in_hdoc = false;
	cmd->append_mode = false;
	cmd->start_ptr = NULL;
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd->argv[0] && cmd->fd_in == 0 && cmd->fd_out == 1);
}
