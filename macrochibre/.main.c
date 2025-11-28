/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 11:44:27 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static inline void	raboushell(char *input, t_env *env)
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

static inline bool	init_env(t_env *env, char **envp)
{
	if (safe_lalloc(&env->envp, 1, env)
		|| safe_lalloc(&env->exportp, 1, env)
		|| builtin_export(envp, env))
		return (true);
	env->empty_string[0] = '\0';
	env->empty_list[0] = NULL;
	env->empty_list[1] = NULL;
	env->err = SUCCESS;
	env->is_ctrl = false;
	env->history = NULL;
	env->update_history = true;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*input;

	(void) argc;
	(void) argv;
	if (!init_env(&env, envp))
	{
		while (!is_end_of_raboushell(&env))
		{
			if (!get_line(&input, "raboushell> ", &env))
			{
				raboushell(input, &env);
				free(input);
			}
		}
	}
	exit_raboushell(&env);
}
