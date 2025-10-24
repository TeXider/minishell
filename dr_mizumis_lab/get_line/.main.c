/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:29:10 by almighty          #+#    #+#             */
/*   Updated: 2025/10/24 10:43:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static inline void	init_env(t_env *env, char **envp)
{
	env->envp = envp;
	env->empty_string[0] = '\0';
	env->empty_list[0] = NULL;
	env->empty_list[1] = NULL;
	env->err = 0;
	env->prompt_len = 5;
}

int main(int argc, char **argv, char **envp)
{
	t_env	env;

	(void) argc;
	(void) argv;
	init_env(&env, envp);
	char *str;
	while(1)
	{
		write(1, "caca>", 5);
		get_line(&str, "caca>", &env);
		write(1, "\n", 1);
		for (int i = 0; str[i]; i++)
			write(1, str + i, 1);
		write(1, "\n", 1);
		free(str);
	}
}