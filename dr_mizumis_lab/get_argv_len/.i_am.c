/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .i_am.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/09/29 08:45:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	t_env	env;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(t_var *) * 3);
	env.envp_len = 3;
	env.envp[0] = malloc(sizeof(t_var)); env.envp[1] = malloc(sizeof(t_var)); env.envp[2] = malloc(sizeof(t_var));
	env.envp[0]->name = "caca"; env.envp[1]->name = "fesse"; env.envp[2]->name = "prout";
	env.envp[0]->val = ""; env.envp[1]->val = " balle trou"; env.envp[2]->val = "fra ka ka ";
	char	*input = malloc(500 * sizeof(char));
	input[read(0, input, 499)] = '\0';
	size_t argv_len;
	if (get_argv_len(input, &argv_len, &env))
		printf("ti as tié mon frrreere li!\n");
	else
		printf("argv : %zu\n", argv_len);
	free(input);
	free(env.envp[0]); free(env.envp[1]); free(env.envp[2]);
	free(env.envp);
}
