/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 10:49:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"
#include "../includes/builtins.h"

int	g_sig = 0;

static inline bool	init_env(t_env *env, char **envp)
{
	env->get_line_env.history = NULL;
	env->get_line_env.is_ctrl = false;
	env->get_line_env.update_history = true;
	env->get_line_env.main_env = env;
	env->get_line_env.line_count = 0;
	env->in_fork = false;
	env->envp_len = 0;
	env->exportp_len = 0;
	env->saved_std_in = FD_NULL;
	env->saved_std_out = FD_NULL;
	init_signals();
	if (safe_lalloc(&env->envp, 1, env)
		|| safe_lalloc(&env->exportp, 1, env)
		|| ((*envp) && builtin_export(envp, env)))
		return (true);
	env->children_count = 0;
	env->end_of_raboushell = false;
	env->err = SUCCESS;
	env->exit_code = 0;
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*input;

	(void) argc;
	(void) argv;
	if (!init_env(&env, envp))
	{
		while (g_sig != SIGNAL_EXIT && !env.in_fork && !env.end_of_raboushell)
		{
			if (!get_line(&input, "raboushell> ", &env.get_line_env))
			{
				raboushell(input, &env);
				if (env.err)
					throw_error(&env);
				free(input);
			}
			if (g_sig == SIGNAL_INT)
				handle_sigint(&env);
		}
	}
	if (env.err)
		throw_error(&env);
	exit_raboushell(&env);
}
