/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/12/08 12:28:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	init_get_redir(t_cmd_parsing *cmdp, t_rtype *type)
{
	cmdp->curr_redir = cmdp->cmd->redirv + cmdp->redirv_i;
	cmdp->curr_redir->name = NULL;
	cmdp->curr_redir->type = EMPTY_REDIR;
	*type = HDOC * (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<')
		+ APPND * (*(cmdp->str) == '>' && *(cmdp->str + 1) == '>');
	*type += !(*type) * (IN * (*(cmdp->str) == '<')
			+ OUT * (*(cmdp->str) == '>'));
	cmdp->str += 1 + (*type == HDOC || *type == APPND);
	skip_spaces(&cmdp->str);
}

static void	add_char_to_name(t_cmd_parsing *cmdp, size_t *redir_name_i)
{
	if (cmdp->sep != ' ' || *(cmdp->str) != ' ')
	{
		cmdp->curr_redir->name[*redir_name_i] = *(cmdp->str);
		(*redir_name_i)++;
	}
	cmdp->str++;
}

static void	update_sep(t_cmd_parsing *cmdp, bool *has_quotes)
{
	set_sep(cmdp);
	*has_quotes = true;
	cmdp->str++;
}

static int	get_redir_name(t_cmd_parsing *cmdp, bool is_hdoc, t_env *env)
{
	size_t	len;
	size_t	redir_name_i;
	bool	has_quotes;

	if (get_redir_name_len(cmdp, &len, is_hdoc, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(&cmdp->curr_redir->name, len, env))
		return (FATAL_SYS_ERR);
	has_quotes = false;
	redir_name_i = 0;
	while (!is_end_of_redir(cmdp))
	{
		if (change_of_sep(cmdp))
			update_sep(cmdp, &has_quotes);
		else if (!is_hdoc && is_var(cmdp))
			expand(cmdp, env);
		else
			add_char_to_name(cmdp, &redir_name_i);
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	return (SUCCESS + HAS_QUOTES * has_quotes);
}

bool	get_redir(t_cmd_parsing *cmdp, t_env *env)
{
	int		status;
	t_rtype	type;

	init_get_redir(cmdp, &type);
	status = get_redir_name(cmdp, (type == HDOC), env);
	if (status == FATAL_SYS_ERR)
		return (true);
	if (status == AMBI_REDIR_ERR)
	{
		if (get_raw_arg(&cmdp->curr_redir->name, cmdp, env))
			return (true);
		type = AMBI_REDIR;
		go_to_end_of_arg(cmdp, env);
	}
	if (type == HDOC && get_hdoc(cmdp, (status != HAS_QUOTES), env))
		return (true);
	if ((type == IN || type == AMBI_REDIR) && cmdp->cmd->is_fd_in_hdoc)
		safe_close(&cmdp->cmd->fd_in, STD_IN);
	cmdp->cmd->is_fd_in_hdoc = (type == HDOC);
	cmdp->curr_redir->type = type * (type != HDOC);
	cmdp->redirv_i += (type != HDOC);
	return (false);
}
