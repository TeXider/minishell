/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:59:03 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:59:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void	wait_children(t_env *env)
{
	pid_t	wait_pid;
	int		status;

	wait_pid = wait(&status);
	while (wait_pid != -1)
	{
		set_exit_code((wait_pid == env->last_pid) 
			* (WIFEXITED(status) * WEXITSTATUS(status)
			+ WIFSIGNALED(status) * (128 + WTERMSIG(status))), env);
		wait_pid = wait(&status);
	}
}

void	raboushell(char *input, t_env *env)
{
	t_cmd	*cmd_list;
	size_t	cmd_list_len;
	
	cmd_list = NULL;
	if (!get_cmd_line(input, &cmd_list, &cmd_list_len, env))
	{
		exec_cmd_line(cmd_list, cmd_list_len, env);
		wait_children(env);
	}
	free_cmd_list(cmd_list, cmd_list_len);
}
