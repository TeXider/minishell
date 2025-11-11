/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/11/11 10:34:17 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_get_redir(t_cmd_parsing *cmdp, t_rtype *type)
{
	cmdp->curr_redir = cmdp->cmd->redirv + cmdp->redirv_i;
	*type = HDOC * (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<')
			+ APPND * (*(cmdp->str) == '>' && *(cmdp->str + 1) == '>');
	*type += !(*type) * (IN * (*(cmdp->str) == '<')
			+ OUT * (*(cmdp->str) == '>'));
	cmdp->str += 1 + (*type == HDOC || *type == APPND);
	skip_spaces(&cmdp->str);
}

static void	add_char_to_name(t_cmd_parsing *cmdp, size_t *i)
{
	if (cmdp->sep != ' ' || *(cmdp->str) != ' ')
	{
		cmdp->curr_redir->name[*i] = *(cmdp->str);
		(*i)++;
	}
	cmdp->str++;
}

static void	update_sep(t_cmd_parsing *cmdp, bool *has_quotes)
{
	set_sep(cmdp);
	*has_quotes = true;
	cmdp->str++;
}

static int	get_redir_name(t_cmd_parsing *cmdp, t_rtype type, t_env *env)
{
	size_t	len;
	size_t	i;
	bool	has_quotes;

	if (get_redir_name_len(cmdp->str, &len, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(&cmdp->curr_redir->name, len, env))
		return (SYS_ERR);
	has_quotes = false;
	i = 0;
	while (!is_end_of_redir(cmdp))
	{
		if (change_of_sep(cmdp))
			update_sep(cmdp, &has_quotes);
		else if (type != HDOC && is_var(cmdp))
			expand(cmdp, env);
		else
			add_char_to_name(cmdp, &i);
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
	status = get_redir_name(cmdp, type, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
	{
		if (status == AMBI_REDIR_ERR)
			create_error(cmdp->str, AMBI_REDIR_ERR, env);
		return (true);
	}
	cmdp->curr_redir->type = type;
	if (type == HDOC && get_hdoc(cmdp, (status == HAS_QUOTES), env))
		return (true);
	if (type != HDOC && cmdp->curr_redir->type == HDOC)
	{
		safe_close(&cmdp->cmd->fd_in);
		cmdp->curr_redir->type == EMPTY_REDIR;
	}
	cmdp->redirv_i++;
	return (false);
}

