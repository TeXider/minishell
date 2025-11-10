/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:55:49 by almighty          #+#    #+#             */
/*   Updated: 2025/11/10 12:41:06 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	write_in_hdoc(t_cmd_parsing *cmdp, bool has_expand, int write_fd,
	t_env *env)
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

static bool	open_hdoc(char *del, int write_fd, bool has_expand, t_env *env)
{
	bool			res;
	size_t			i;
	t_cmd_parsing	tmp_cmdp;
	char			*tmp_str;

	simple_init_cmd_parsing(&tmp_cmdp);
	env->update_history = false;
	while (!is_end_of_hdoc(&tmp_cmdp))
	{
		i = -1;
		if (get_line(&tmp_str, "> ", env))
			return (true);
		tmp_cmdp.str = tmp_str;
		while (*(tmp_cmdp.str) && *(tmp_cmdp.str) != '\n')
			write_in_hdoc(&tmp_cmdp, has_expand, write_fd, env);
	}
	env->update_history = true;
	return (false);
}

bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env)
{
	int		hdoc_fds[2];

	if (pipe(hdoc_fds))
	{
		create_error(SYS_ERR, "pipe()", env);
		return (true);
	}
	if (open_hdoc(cmdp->curr_redir->name, hdoc_fds[P_WRITE], has_expand, env))
	{
		safe_close(hdoc_fds + P_READ);
		safe_close(hdoc_fds + P_WRITE);
		return (true);
	}
	if (cmdp->curr_redir->type == HDOC)
		safe_close(&cmdp->cmd->fd_in);
	cmdp->cmd->fd_in = hdoc_fds[P_READ];
	cmdp->cmd->fd_in_type = HDOC;
	safe_close(hdoc_fds + P_READ);
	safe_close(hdoc_fds + P_WRITE);
	return (false);
}
