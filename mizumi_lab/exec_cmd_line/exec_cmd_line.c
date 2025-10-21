/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:16:20 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 12:26:48 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_line(char **line, t_env *env)
{
	pid_t	pid;
	t_cmd	cmd;
	
	while (**line && **line != '\n')
	{
		pid = fork();
		if (pid == -1)
			throw_error();
		if (!pid)
		{
			if (get_cmd(&cmd))
				throw_err();
			
		}
		else
			go_t
	}
}