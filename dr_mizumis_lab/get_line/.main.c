/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:29:10 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 15:37:10 by almighty         ###   ########.fr       */
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
	env->prompt_len = 6;
	env->is_ctrl = false;
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
		//write(1, "caca> ", 6);
		get_line(&str, "caca> ", &env);
		// t_line line;
		// write(1, "JAIMELESBITES", 13);
		// line.count = 13;
		// line.index = 13;
		// int cols;
		// get_term_cols(&cols, &env);
		// reset_line_output(&line, cols, &env);
		// printf("\nindex : %zu\ncount : %zu\ncol : %d\n", line.index, line.count, get_curr_col(&line, cols, &env));
		for (int i = 0; str[i]; i++)
			write(1, str + i, 1);
		free(str);
		(void) str;
	}
}