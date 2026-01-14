/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redundant_subshells.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:40:52 by almighty          #+#    #+#             */
/*   Updated: 2026/01/07 11:48:43 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	remove_redundant_subshells(t_shell_op *shell_op)
{
	t_shell_op	*tmp;

	while (((t_shell_op *) shell_op->op)->is_subshell
		&& ((t_shell_op *) shell_op->op)->op_type == EMPTY_OP)
	{
		tmp = shell_op->op;
		shell_op->op = ((t_shell_op *) shell_op->op)->op;
		free(tmp);
	}
}
