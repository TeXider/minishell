/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/11/13 16:09:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	env.empty_list[0] = NULL; env.empty_list[1] = NULL;
	env.empty_string[0] = '\0';
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller=   c "; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=rin tin tin ";
	env.err = 0;
	env.is_ctrl = false;
	env.history = NULL;
	env.update_history = true;
	char	*input;
	t_cmd	*cmd_list;
	size_t	cmd_list_len;
	t_cmd	empty_cmd;
	set_new_cmd(&empty_cmd, &env);
	cmd_list = &empty_cmd;
	get_line(&input, "paf malfaisant> ", &env);
	if (get_cmd_line(input, &cmd_list, &cmd_list_len, &env))
	{
		print_str("ti as tié mon frrreere li!\n");
		return (1);
	}
	size_t	i;
	print_str("\n\n\n");
	for (i = 0; i < cmd_list_len; i++)
	{
		write(1, "---SOC---\n\n", 11);
		if (cmd_list[i].argv && cmd_list[i].argv[0])
		{
			for (size_t j = 0; cmd_list[i].argv[j]; j++)
				print_str(cmd_list[i].argv[j]);
		}
		if (cmd_list[i].fd_in != STD_IN)
		{
			pid_t child;
			child = fork();
			if (!child)
			{
				char *argv[2];
				argv[0] = "cat";
				argv[1] = NULL;
				dup2(cmd_list[i].fd_in, STD_IN);
				execve("/usr/bin/cat", argv, envp);
			}
		}
		if (cmd_list[i].argv && *(cmd_list[i].argv))
		{
			for (size_t j = 0; cmd_list[i].argv[j]; j++)
				free(cmd_list[i].argv[j]);
			free(cmd_list[i].argv);
		}
		print_str("Redirs :\n");
		for (size_t j = 0; j < cmd_list[i].redirv_len && cmd_list[i].redirv[j].type != AMBI_REDIR; j++)
		{
			print_str(cmd_list[i].redirv[j].name);
			//write(1, "\n", 1);
			safe_free((void **) &cmd_list[i].redirv[j].name);
		}
		write(1, "\n---EOC---\n\n", 12);
		free(cmd_list[i].redirv);
		if (cmd_list[i].fd_out != STD_OUT)
			close(cmd_list[i].fd_out);
		if (cmd_list[i].fd_in != STD_IN)
			close(cmd_list[i].fd_in);
	}
	if (i)
		free(cmd_list);
	free(input);
	free(env.envp);
}