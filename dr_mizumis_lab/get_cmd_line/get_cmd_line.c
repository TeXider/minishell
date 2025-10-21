/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:03:27 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 12:04:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_cmd_line(char **line, t_cmd **cmd_list, t_env *env)
{
	size_t	cmd_list_len;
	size_t	i;
	
	if (check_line_parsing(*line, &cmd_list_len, env))
		return (true);
	if (!cmd_list_len)
		return (false);
	if (safe_cmdlalloc(cmd_list, cmd_list_len, env))
		return (true);
	i = 0;
	while (**line && **line != '\n')
	{
		set_new_cmd(*cmd_list + i, env);
		if (get_cmd(line, *cmd_list + i++, env))
			return (true);
		(*line) += (**line == '|');
	}
	return (false);
}
