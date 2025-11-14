/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/11/14 12:20:47 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	init_env(t_env *env, char **envp)
{
	env->envp = envp;
	env->empty_string[0] = '\0';
	env->empty_list[0] = NULL;
	env->empty_list[1] = NULL;
	env->err = 0;
	env->is_ctrl = false;
	env->history = NULL;
	env->update_history = true;
}

static inline void	raboushell(char *input, t_env *env)
{
	t_cmd	*cmd_list;
	size_t	cmd_list_len;
	
	if (get_cmd_line(input, &cmd_list, &cmd_list_len, env)
		|| exec_cmd_line(cmd_list, cmd_list_len, env))
		throw_error(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*input;

	(void) argc;
	(void) argv;
	init_env(&env, envp);
	while (true)
	{
		if (get_line(&input, "raboushell> ", &env))
			return (true);
		raboushell(input, &env);
		free(input);
	}
	return (0);
}
