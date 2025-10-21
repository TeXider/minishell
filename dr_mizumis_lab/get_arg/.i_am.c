/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .i_am.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/10/07 14:49:12 by almighty         ###   ########.fr       */
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
	t_env	env;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(char *) * 4);
	env.envp_len = 3;
	env.envp[3] = NULL;
	env.envp[0] = "caca="; env.envp[1] = "fesse=balletrou"; env.envp[2] = "prout=fra ka ka ";
	char	*input = malloc(500 * sizeof(char));
	t_cmd	cmd;
	cmd.argv = malloc(sizeof(char *) * 100);
	for (size_t i = 0; i < 100; i++)
		cmd.argv[i] = NULL;
	input[read(0, input, 499)] = '\0';
	char *tmp = input;
	size_t arg_i;
	arg_i = 0;
	if (get_arg(&tmp, &cmd, &arg_i, &env))
		printf("ti as tié mon frrreere li!\n");
	for (size_t i = 0; cmd.argv[i]; i++)
		print_str(cmd.argv[i]);
	write(1, "\n\n", 2);
	free(input);
	for (size_t i = 0; cmd.argv[i]; i++)
		free(cmd.argv[i]);
	free(cmd.argv);
	free(env.envp);
}
