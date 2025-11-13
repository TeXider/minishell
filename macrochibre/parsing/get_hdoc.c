/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:55:49 by almighty          #+#    #+#             */
/*   Updated: 2025/11/13 16:19:06 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_in_hdoc(t_cmd_parsing *cmdp, bool has_expand, int write_fd,
	t_env *env)
{
	while (cmdp->str && (cmdp->in_expand
		|| (*(cmdp->str) && *(cmdp->str) != '\n')))
	{
		if (has_expand && is_var(cmdp))
			expand(cmdp, env);
		else
		{
			write(write_fd, cmdp->str, 1);
			cmdp->str++;
		}
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	write(write_fd, "\n", (cmdp->str != NULL));
}

static bool	open_hdoc(char *del, int write_fd, bool has_expand, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	char			*line;

	simple_init_cmd_parsing(&tmp_cmdp);
	line = NULL;
	env->update_history = false;
	while (!is_end_of_hdoc(del, line))
	{
		tmp_cmdp.str = line;
		write_in_hdoc(&tmp_cmdp, has_expand, write_fd, env);
		safe_free((void **) &line);
		if (get_line(&line, "> ", env))
			return (true);
	}
	safe_free((void **) &line);
	env->update_history = true;
	return (false);
}

bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env)
{
	int		hdoc_fds[2];

	if (pipe(hdoc_fds))
	{
		create_error("pipe()", SYS_ERR, env);
		return (true);
	}
	if (open_hdoc(cmdp->curr_redir->name, hdoc_fds[P_WRITE], has_expand, env))
	{
		close(hdoc_fds[P_READ]);
		close(hdoc_fds[P_WRITE]);
		return (true);
	}
	cmdp->cmd->fd_in = hdoc_fds[P_READ];
	cmdp->cmd->fd_in_type = HDOC;
	close(hdoc_fds[P_WRITE]);
	safe_free((void **) &cmdp->curr_redir->name);
	return (false);
}

//int	main(int argc, char **argv)
//{
//	(void) argc; (void) argv;
//	t_env	env;
//	env.is_ctrl = false;
//	env.history = NULL;
//	env.empty_list[0] = NULL;
//	env.empty_list[1] = NULL;
//	env.empty_string[0] = '\0';
//	env.envp = malloc(sizeof(char *) * 4);
//	env.envp[3] = NULL;
//	env.envp[0] = "bousiller=   c "; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=rin tin tin ";
//	t_cmd_parsing cmdp;
//	t_cmd		cmd;
//	t_redir		redir;
//	cmdp.argv_len = 0;
//	cmdp.saved_str = NULL;
//	cmdp.sep = ' ';
//	cmdp.cmd = &cmd;
//	cmdp.str = malloc(sizeof(char) * 257);
//	ssize_t rd = read(1, cmdp.str, 256);
//	if (rd == -1)
//		return (1);
//	cmdp.str[rd] = '\0';
//	redir.name = cmdp.str;
//	redir.type = HDOC;
//	cmdp.curr_redir = &redir;
//	redir.name = cmdp.str;
//	cmd.fd_in = -1;
//	cmd.fd_in_type = EMPTY_REDIR;
//	if (get_hdoc(&cmdp, 1, &env))
//		printf("Yo mama so fat she broke my hdocs\n");
//	size_t	i;
//	ssize_t	size;
//	while (true)
//	{
//		size = read(cmd.fd_in, cmdp.str, 1);
//		if (!size)
//			break ;
//		for  (i = 0; i < (size_t)size; i++)
//			write(1, cmdp.str + i, 1);
//	}
//}