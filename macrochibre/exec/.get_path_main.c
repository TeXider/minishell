/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .get_path_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:26:24 by almighty          #+#    #+#             */
/*   Updated: 2025/11/27 14:51:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	t_env env;
	t_cmd cmd;

	env.envp = envp;
	cmd.argv = malloc(sizeof(char *) * 2);
	cmd.argv[0] = argv[1];
	cmd.argv[1] = NULL;
	cmd.cmd_name_is_path = false;
	env.err = SUCCESS;
	if (get_path(&cmd, &env))
		return (1);
	char *tmp = cmd.path;
	while (*(cmd.path))
		write(1, cmd.path++, 1);
	write(1, "\n", 1);
	if (tmp != cmd.argv[0])
		free(tmp);
	free(cmd.argv);
}