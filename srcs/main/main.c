/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 11:59:30 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline bool	init_env(t_env *env, char **envp)
{
	if (safe_lalloc(&env->envp, 1, env)
		|| safe_lalloc(&env->exportp, 1, env)
		|| builtin_export(envp, env))
		return (true);
	env->get_line_env.history = NULL;
	env->get_line_env.is_ctrl = false;
	env->get_line_env.update_history = true;
	env->get_line_env.main_env = env;
	env->in_fork = false;
	env->end_of_raboushell = false;
	env->err = SUCCESS;
	env->exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*input;

	(void) argc;
	(void) argv;
	if (!init_env(&env, envp))
	{
		while (!env.in_fork && !env.end_of_raboushell)
		{
			if (!get_line(&input, "raboushell> ", &env))
			{
				raboushell(input, &env);
				free(input);
			}
		}
	}
	throw_error(&env);
	exit_raboushell(&env);
}
