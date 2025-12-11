/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:55:49 by almighty          #+#    #+#             */
/*   Updated: 2025/12/11 19:45:14 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	print_hdoc_warning(char *del, t_env *env)
{
	size_t	del_len;

	print_raboushell();
	write(2, "\e[1m\e[38;5;202mwarning: \e[0mhere-document at line ", 51);
	print_uint(env->get_line_env.line_count);
	write(2, " delimited by end-of-file (wanted `", 35);
	del_len = 0;
	while (del[del_len])
		del_len++;
	write(2, del, del_len);
	write(2, "')\n", 3);
}

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
	env->get_line_env.prompt_len = 2;
	env->get_line_env.update_history = false;
	while (!is_end_of_hdoc(del, line))
	{
		tmp_cmdp.str = line;
		write_in_hdoc(&tmp_cmdp, has_expand, write_fd, env);
		safe_free((void **) &line);
		if (get_line(&line, "> ", &env->get_line_env))
		{
			env->get_line_env.update_history = true;
			return (true);
		}
	}
	safe_free((void **) &line);
	env->get_line_env.update_history = true;
	return (false);
}

bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env)
{
	int		hdoc_fds[2];

	safe_close(&cmdp->cmd->fd_in, STD_IN);
	if (pipe(hdoc_fds))
	{
		create_error("pipe()", SYS_ERR, env);
		return (true);
	}
	if (open_hdoc(cmdp->curr_redir->name, hdoc_fds[P_WRITE], has_expand, env)
		&& g_sig != SIGNAL_EXIT)
	{
		safe_free((void **) &cmdp->curr_redir->name);
		close(hdoc_fds[P_READ]);
		close(hdoc_fds[P_WRITE]);
		return (true);
	}
	cmdp->cmd->fd_in = hdoc_fds[P_READ];
	close(hdoc_fds[P_WRITE]);
	if (g_sig == SIGNAL_EXIT)
	{
		print_hdoc_warning(cmdp->curr_redir->name, env);
		g_sig = 0;
	}
	safe_free((void **) &cmdp->curr_redir->name);
	return (false);
}
