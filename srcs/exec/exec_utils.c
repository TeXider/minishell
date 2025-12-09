/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:02:11 by almighty          #+#    #+#             */
/*   Updated: 2025/12/09 12:51:13 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

inline bool	save_std_fds(t_env *env)
{
	if (env->saved_std_out != FD_NULL || env->saved_std_out != FD_NULL)
		return (false);
	env->saved_std_in = dup(STD_IN);
	env->saved_std_out = dup(STD_OUT);
	if (env->saved_std_out == FD_NULL || env->saved_std_out == FD_NULL)
	{
		create_error("dup()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	dup2_std(int new_std_in, int new_std_out, t_env *env)
{
	if ((new_std_in != FD_NULL && dup2(new_std_in, STD_IN) == -1)
		|| (new_std_out != FD_NULL && dup2(new_std_out, STD_OUT) == -1))
	{
		create_error("dup2()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	is_end_of_exec(size_t cmd_list_i, size_t cmd_list_len, t_env *env)
{
	return (g_sig || env->in_fork || cmd_list_i >= cmd_list_len
		|| env->err == FATAL_SYS_ERR || env->err == SYS_ERR);
}

inline bool	get_path_var(char **path_var, t_env *env)
{
	size_t	i;

	i = -1;
	while (env->envp[++i])
	{
		if (env->envp[i][0] == 'P'
			&& env->envp[i][1] == 'A'
			&& env->envp[i][2] == 'T'
			&& env->envp[i][3] == 'H'
			&& env->envp[i][4] == '=')
		{
			*path_var = env->envp[i] + 5;
			return (**path_var == '\0');
		}
	}
	return (true);
}
