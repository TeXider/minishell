/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .redir_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:17:55 by almighty          #+#    #+#             */
/*   Updated: 2025/11/13 15:23:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	(void) argc; (void) argv;
	t_env	env;
	env.is_ctrl = false;
	env.history = NULL;
	env.empty_list[0] = NULL;
	env.empty_list[1] = NULL;
	env.empty_string[0] = '\0';
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller=   c "; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=rin tin tin ";
	t_cmd_parsing cmdp;
	t_cmd		cmd;
	t_redir		redir;
	cmdp.argv_len = 0;
	cmdp.saved_str = NULL;
	cmdp.sep = ' ';
	cmdp.str = malloc(sizeof(char) * 257);
	ssize_t rd = read(1, cmdp.str, 256);
	if (rd == -1)
		return (1);
	cmdp.str[rd] = '\0';
	init_cmd_parsing(&cmdp, cmdp.str);
	cmdp.cmd = &cmd;
	redir.name = NULL;
	redir.type = EMPTY_REDIR;
	cmdp.cmd->redirv = &redir;
	cmd.fd_in = -1;
	cmd.fd_in_type = EMPTY_REDIR;
	if (get_redir(&cmdp, &env))
		printf("Yo mama so fat she broke my redirs\n");
	size_t	i;
	//ssize_t	size;
	for (i = 0; cmd.redirv[0].name[i]; i++)
		write(1, cmd.redirv[0].name + i, 1);
	write(1, "\n", 1);
}