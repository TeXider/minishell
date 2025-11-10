/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/11/10 11:13:40 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	handle_redir_err(t_cmd_parsing *cmdp, t_err status, t_env *env)
{
	if (status == AMBI_REDIR_ERR)
		create_error(cmdp->str, AMBI_REDIR_ERR, env);
	return (true);
}

static void	add_char_to_name(t_cmd_parsing *cmdp, size_t *i)
{
	if (cmdp->sep != ' ' || *(cmdp->str) != ' ')
	{
		cmdp->cmd->redirv[cmdp->redirv_i].name[*i] = *(cmdp->str);
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
	if (safe_challoc(&cmdp->cmd->redirv[cmdp->redirv_i].name, len, env))
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

	cmdp->cmd->redirv[cmdp->redirv_i].name = NULL;
	type = HDOC * (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<')
			+ APPND * (*(cmdp->str) == '>' && *(cmdp->str + 1) == '>');
	type += !type * (IN * (*(cmdp->str) == '<')
			+ OUT * (*(cmdp->str) == '>'));
	cmdp->str += 1 + (type == HDOC || type == APPND);
	skip_spaces(&cmdp->str);
	status = get_redir_name(cmdp, type, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
	{
		handle_redir_err(cmdp, status, env);
		return (true);
	}
	cmdp->cmd->redirv[cmdp->redirv_i].type = type;
	if (type == HDOC /*&& open_hdoc(cmdp, env)*/)
		return (true);
	cmdp->redirv_i++;
	return (false);
}

