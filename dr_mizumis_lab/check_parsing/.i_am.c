/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .i_am.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 12:04:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_str(char *str)
{
	while (*str)
		write(1, str++,1);
	write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	char *empty_list[2];
	t_env	env;
	empty_list[0] = NULL; empty_list[1] = NULL;
	env.empty_list = empty_list;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "caca="; env.envp[1] = "fesse=balletrou"; env.envp[2] = "prout=fra ka ka ";
	char	*input = malloc(500 * sizeof(char));
	input[read(0, input, 499)] = '\0';
	char *tmp = input;
	size_t	cll;
	check_line_parsing(tmp, &cll, &env);
	printf("cll: %zu\n", cll);
	free(input);
	free(env.envp);
}
