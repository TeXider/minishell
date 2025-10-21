/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 11:43:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	grnl_init(t_get_redir_name_len *grnl)
{
	grnl->has_arg = false;
	grnl->var_is_sep = false;
	grnl->sep = ' ';
}

static inline bool	get_redir_name_len(char *redir, size_t *len, bool is_hdoc, t_env *env)
{
	t_get_redir_name_len	grnl;
	
	*len = 0;
	grnl_init(&grnl);
	while (!is_end_of_arg(*redir, grnl.sep))
	{
		if ((grnl.sep == ' ' && is_quote(*redir)) || *redir == grnl.sep)
			set_sep(&grnl.sep, *redir);
		else if (is_var(redir, grnl.sep) && !is_hdoc)
		{
			if (get_redir_expand_len(&redir, len, &grnl, env))
				return (true);
		}
		else if (grnl.var_is_sep && grnl.has_arg)
			return (true);
		else
		{
			(*len)++;
			grnl.has_arg = true;
			grnl.var_is_sep = false;
		}
		redir++;
	}
	return (!*len);
}

static inline int	get_redir_name(char **redir, bool is_hdoc, char **name,
			t_env *env)
{
	t_get_redir_name	grn;

	if (get_redir_name_len(*redir, &grn.len, is_hdoc, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(name, grn.len, env))
		return (SYS_ERR);
	grn.i = 0;
	grn.has_quotes = false;
	grn.sep = ' ';
	while (!is_end_of_arg(**redir, grn.sep))
	{
		if ((grn.sep == ' ' && is_quote(**redir)) || **redir == grn.sep)
			set_sep(&grn.sep, **redir);
		else if (is_var(*redir, grn.sep) && !is_hdoc)
			redir_expand(redir, *name, &grn, env);
		else
			(*name)[grn.i++] = **redir;
		grn.has_quotes |= (grn.sep != ' ');
		(*redir)++;
	}
	return (-1 - grn.has_quotes);
}

bool	get_redir(char **redir, t_cmd *res, t_env *env)
{
	char	*name;
	int		status;
	t_type	type;
	int		fd;

	type = HDOC *(**redir == '<' && (*redir)[1] == '<')
			+ APPND * (**redir == '>' && (*redir)[1] == '>');
	type += !type * (IN * (**redir == '<') + OUT * (**redir == '>') - type);
	*redir += 1 + (type == HDOC || type == APPND);
	skip_spaces(redir);
	status = get_redir_name(redir, (type == HDOC), &name, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
		return (handle_redir_err(*redir, status, env));
	fd = open_redir(name, type, (status == -2), env);
	if (fd == -1)
		return (true);
	if (close_prev_redir(res, type, env))
		return (true);
	res->fd_in += (fd - res->fd_in) * (type <= IN);
	res->append_mode = (type == APPND || (res->append_mode && type >= OUT));
	res->fd_out += (fd - res->fd_out) * (type >= OUT);
	res->is_fd_in_pipe &= !(type <= IN);
	res->is_fd_out_pipe &= !(type >= OUT);
	free(name);
	return (false);
}
