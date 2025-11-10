/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:55:49 by almighty          #+#    #+#             */
/*   Updated: 2025/11/10 11:39:41 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	open_hdoc(char *del, int *write_fd, bool has_expand, t_env *env)
{
	bool	res;
	size_t	i;
	char	*input;

	input = NULL;
	while (!get_line(&input, "> ", env) && !is_end_of_hdoc(input, del))
	{
		i = -1;
		while (input[++i])
		{
			if (is_var(input, ' '))
				print_expand(&input, *write_fd, env);
			else
				write(*write_fd, input, 1);
		}
	}
	safe_close(write_fd);
	return (safe_free(&input));
}

bool	get_hdoc(t_cmd_parsing *cmdp, bool has_quotes, t_env *env)
{
	char	*del;
	bool	del_has_quotes;
	int		hdoc_fds[2];

	hdoc_fds[P_READ] = -1;
	hdoc_fds[P_WRITE] = -1;
	if (pipe(hdoc_fds)
		|| open_hdoc(del, hdoc_fds + P_WRITE, del_has_quotes, env))
	{
		safe_close(hdoc_fds + P_READ);
		safe_close(hdoc_fds + P_WRITE);
		safe_free(&del);
		return (true);
	}
	if (cmdp->curr_redir->type == HDOC)
		safe_close(&cmdp->cmd->fd_in);
	dst->fd_in = hdoc_fds[P_READ];
	safe_close(hdoc_fds + P_READ);
	safe_close(hdoc_fds + P_WRITE);
	safe_free(&del);
	return (false);
}
