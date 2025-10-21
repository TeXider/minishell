/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 11:42:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_cmd(char **cmd, t_cmd *res, t_env *env)
{
	size_t	argv_len;
	size_t	arg_i;

	if (get_argv_len(*cmd, &argv_len, env)
		|| safe_lalloc(&(res->argv), argv_len, env))
		return (false);
	arg_i = 0;
	while (!is_end_of_cmd(**cmd, ' '))
	{
		if (**cmd == '>' || **cmd == '<')
		{
			if (get_redir(cmd, res, env))
				return (true);
		}
		else if (**cmd != ' ')
		{
			if (get_arg(cmd, res, &arg_i, env))
				return (true);
		}
		else
			(*cmd)++;
	}
	return (false);
}
