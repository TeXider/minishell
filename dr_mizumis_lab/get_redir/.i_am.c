/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .i_am.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/10/02 11:59:54 by almighty         ###   ########.fr       */
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
	env.envp[0]->val = " bite "; env.envp[1]->val = "a    "; env.envp[2]->val = "   b";
	char	*input = malloc(501 * sizeof(char));
	int rd = read(0, input, 499);
	if (rd < 0 || rd > 500)
	{
		free(input);
		return (1);
	}
	input[rd] = '\0';
	t_cmd	cmd;
	cmd.fd_in = 0;
	cmd.fd_out = 1;
	cmd.append_mode = false;
	char *tmp = input;
	if (get_redir(&tmp, &cmd, &env))
		printf("ti as tié mon frrreere li!\n");
	else
		printf("fd_in : %d, fd_out: %d, appnd : %d\n", cmd.fd_in, cmd.fd_out, cmd.append_mode);
	if (cmd.fd_in != 0 && cmd.fd_in != 1234)
	{
		rd = read(cmd.fd_in, input, 499);
		input[rd + (rd < 0)] = '\0';
		printf("%s\n\n\n", input);
	}
	if (cmd.fd_out != 1)
	{
		rd = read(cmd.fd_out, input, 499);
		input[rd + (rd < 0)] = '\0';
		printf("%s\n\n\n", input);
	}
	free(input);
	free(env.envp[0]); free(env.envp[1]); free(env.envp[2]);
	free(env.envp);
}
