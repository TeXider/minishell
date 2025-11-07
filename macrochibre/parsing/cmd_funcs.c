/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:15:58 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 10:22:42 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline void	set_new_cmd(t_cmd *cmd, t_env *env)
{
	cmd->path = NULL;
	cmd->argv = env->empty_list;
	cmd->redirv = NULL;
	cmd->redirv_len = 0;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
	cmd->fd_in_type = STD;
	cmd->fd_out_type = STD;
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd->argv[0] && cmd->fd_in == 0 && cmd->fd_out == 1);
}
