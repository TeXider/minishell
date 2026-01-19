/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:40:52 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:58 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

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

inline bool	get_raw_arg(char **dst, t_cmd_parsing *cmdp, bool put_in_quotes,
	t_env *env)
{
	char	*tmp_str;
	size_t	i;

	i = 0;
	tmp_str = cmdp->str;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		cmdp->str++;
		i++;
	}
	if (safe_challoc(dst, i + 2 * put_in_quotes, env))
		return (true);
	cmdp->str = tmp_str;
	if (put_in_quotes)
		(*dst)[0] = '`';
	i = put_in_quotes;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		(*dst)[i++] = *(cmdp->str++);
	}
	if (put_in_quotes)
		(*dst)[i] = '\'';
	return (false);
}
