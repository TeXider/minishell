/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:35:34 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 10:20:26 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

inline bool	safe_shell_op_alloc(t_shell_op **dst, t_env *env)
{
	*dst = malloc(sizeof(t_shell_op));
	if (!*dst)
	{
		create_error("malloc()", FATAL_SYS_ERR, env);
		return (true);
	}
	(*dst)->op = NULL;
	(*dst)->is_subshell = false;
	(*dst)->op_type = EMPTY_OP;
	(*dst)->next = NULL;
	return (false);
}

inline bool	safe_cmd_alloc(t_cmd **dst, t_env *env)
{
	*dst = malloc(sizeof(t_cmd));
	if (!*dst)
	{
		create_error("malloc()", FATAL_SYS_ERR, env);
		return (true);
	}
	(*dst)->path = NULL;
	(*dst)->cmd_name_is_path = false;
	(*dst)->argv = NULL;
	(*dst)->redirv = NULL;
	(*dst)->redirv_len = 0;
	(*dst)->fd_in = FD_NULL;
	(*dst)->fd_out = FD_NULL;
	(*dst)->is_fd_in_hdoc = false;
	return (false);
}
