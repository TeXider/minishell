/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:02:11 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 13:26:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

inline bool	is_end_of_exec(t_exec *exec, t_env *env)
{
	return (g_sig | !exec->shell_op || env->end_of_raboushell
		|| env->err == FATAL_SYS_ERR || env->err == SYS_ERR);
}

inline bool	has_to_exec(t_exec *exec, t_env *env)
{
	return (exec->prev_op == EMPTY_OP || exec->prev_op == PIPE_OP
		|| (env->exit_code && exec->prev_op == OR_OP)
		|| (!env->exit_code && exec->prev_op == AND_OP));
}

inline bool	save_std_fds(t_exec *exec, t_env *env)
{
	exec->saved_std_in = dup(STD_IN);
	if (exec->saved_std_in == FD_NULL)
	{
		create_error("dup()", SYS_ERR, env);
		return (true);
	}
	exec->saved_std_out = dup(STD_OUT);
	if (exec->saved_std_out == FD_NULL)
	{
		close(exec->saved_std_in);
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
