/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 13:46:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static inline void	set_cmd_fds(t_cmd *dst, int fd, t_rtype type)
{
	dst->fd_in += (fd - dst->fd_in) * (type <= IN);
	dst->append_mode = (type == APPND || (dst->append_mode && type >= OUT));
	dst->fd_out += (fd - dst->fd_out) * (type >= OUT);
	dst->is_fd_in_pipe &= !(type <= IN);
	dst->is_fd_out_pipe &= !(type >= OUT);
}

static inline void	grnl_init(t_get_redir_name_len *grnl)
{
	grnl->has_arg = false;
	grnl->var_is_sep = false;
	grnl->sep = ' ';
}

static inline bool	get_redir_name_len(char *redir, size_t *len, t_env *env)
{
	t_get_redir_name_len	grnl;

	*len = 0;
	grnl_init(&grnl);
	while (!is_end_of_arg(*redir, grnl.sep))
	{
		if ((grnl.sep == ' ' && is_quote(*redir)) || *redir == grnl.sep)
			set_sep(&grnl.sep, *redir);
		else if (is_var(redir, grnl.sep))
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

static inline t_err	get_redir_name(char **redir, char **name, t_env *env)
{
	t_get_redir_name	grn;

	if (get_redir_name_len(*redir, &grn.len, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(name, grn.len, env))
		return (SYS_ERR);
	grn.i = 0;
	grn.sep = ' ';
	while (!is_end_of_arg(**redir, grn.sep))
	{
		if ((grn.sep == ' ' && is_quote(**redir)) || **redir == grn.sep)
			set_sep(&grn.sep, **redir);
		else if (is_var(*redir, grn.sep))
			redir_expand(redir, *name, &grn, env);
		else
			(*name)[grn.i++] = **redir;
		(*redir)++;
	}
	return (SUCCESS);
}

bool	get_redir(char **redir, char **name, t_cmd *dst, t_env *env)
{
	int		status;
	t_rtype	type;
	int		fd;

	*name = NULL;
	type = IN * (**redir == '<')
		+ OUT * (**redir == '>' && *(*redir + 1) != '>')
		+ APPND * (**redir == '>' && *(*redir + 1) == '>');
	*redir += (type == APPND);
	skip_spaces(redir);
	status = get_redir_name(redir, name, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
		return (handle_redir_err(*redir, status, env));
	fd = open_redir(name, type, (status == -2), env);
	if (fd == -1)
		return (true);
	close_prev_redir(dst, type);
	set_cmd_fds(dst, type, fd);
	return (false);
}
