/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .i_am.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 12:17:57 by almighty         ###   ########.fr       */
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
	// if (get_cmd_line(&tmp, &cmd_list, &env))
	// 	printf("ti as tié mon frrreere li!\n");
	// size_t	i;
	// for (i = 0; !is_empty_cmd(cmd_list + i); i++)
	// {
	// 	if (cmd_list[i].argv && cmd_list[i].argv[0])
	// 	{
	// 		for (size_t j = 0; cmd_list[i].argv[j]; j++)
	// 			print_str(cmd_list[i].argv[j]);
	// 	}
	// 	printf("fdin: %d\n", cmd_list[i].fd_in);
	// 	printf("fdout: %d\n", cmd_list[i].fd_out);
	// 	write(1, "\n\n", 2);
	// 	if (cmd_list[i].argv && *(cmd_list[i].argv))
	// 	{
	// 		for (size_t j = 0; cmd_list[i].argv[j]; j++)
	// 			free(cmd_list[i].argv[j]);
	// 		free(cmd_list[i].argv);
	// 	}
	// 	if (cmd_list[i].fd_out != 1)
	// 		close(cmd_list[i].fd_out);
	// 	if (cmd_list[i].fd_in != 0)
	// 		close(cmd_list[i].fd_in);
	// }
	// if (!i)
	// 	printf("mt\n");
	// else
	// 	free(cmd_list)
	size_t c;
	if (check_line_parsing(tmp, &c, &env))
		return (-1);
	exec_cmd_line(&tmp, c, &env);
	free(env.envp);
}
