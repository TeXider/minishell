/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:29:10 by almighty          #+#    #+#             */
/*   Updated: 2025/10/20 12:44:40 by almighty         ###   ########.fr       */
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
}

int main(int argc, char **argv, char **envp)
{
	t_env	env;

	(void) argc;
	(void) argv;
	init_env(&env, envp);
	if (init_get_line(&env))
		return (1);
	char c;
	while(1)
	{
		read(0, &c, 1);
		if (c != 127)
			write(1, &c, 1);
		else
		{
			write(1, &(int) { 8 }, 1);
			write(1, &(int) { ' ' }, 1);
			write(1, &(int) { 8 }, 1);
		}
	}
}