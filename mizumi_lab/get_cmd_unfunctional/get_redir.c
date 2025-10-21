/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/10/01 10:49:41 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	redir_expand(char **redir, char *name, char sep, t_env *env)
{
	t_var	var;
	size_t	i;

	if (get_var(redir, &var, env))
		return ;
	i = -1;
	while (var.val[++i])
		if (var.val[i] != ' ' || sep != ' ');
			name[*(env->norm_index)++] = var.val[i];
}

static inline size_t	redir_expand_len(char **redir, char sep, t_env *env)
{
	t_var	var;
	size_t	len;
	size_t	i;

	if (get_var(redir, &var, env))
		return (0);
	len = 0;
	i = -1;
	while (var.val[++i])
	{
		if (sep == ' ' && var.val[i] != ' ' && len)
			return (len);
		len += (var.val[i] != ' ' || sep != ' ');
	}
	return (len);
}

static inline bool	get_redir_name_len(char *redir, size_t *len, bool is_hdoc,
			t_env *env)
{
	size_t	tmp_len;
	char	sep;

	*len = 0;
	sep = ' ';
	while (!is_end_of_arg(*redir, sep))
	{
		if (sep == ' ')
			set_sep(&sep, *redir);
		if (sep != '\'' && *redir == '$' && is_var_char(*(redir + 1))
			&& !is_hdoc)
		{
			tmp_len = redir_expand_len(&redir, sep, env);
			if (sep == ' ' && tmp_len && *len)
				return (true);
			*len += tmp_len;
		}
		else
			*len += (sep != *redir);
		if (sep != ' ')
			set_sep(&sep, *redir);
		redir++;
	}
	return (!*len);
}

static inline int	get_redir_name(char **redir, bool is_hdoc, char **name,
			t_env *env)
{
	size_t	len;
	char	sep;
	bool	has_quotes;
	size_t	i;

	if (get_redir_name_len(*redir, &len, is_hdoc, env))
		return (AMBI_REDIR_ERR);
	if (set_challoc(name, len))
		return (SYS_ERR);
	i = 0;
	env->norm_index = &i;
	has_quotes = false;
	sep = ' ';
	while (!is_end_of_arg(**redir, sep))
	{
		set_sep(&sep, **redir);
		has_quotes |= (sep != ' ');
		if (sep != '\'' && **redir == '$' && is_var_char(*(*redir + 1))
			&& !is_hdoc)
			redir_expand(redir, *name, sep, env);
		else
			name[i++] = **redir;
		(*redir)++;
	}
	return (HAS_QUOTES * has_quotes);
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
	fd = open_redir(name, type, status, env);
	if (fd == -1)
		return (true);
	if (close_prev_redir(res, type, env))
		return (true);
	res->fd_in += (fd - res->fd_in) * (type <= 2);
	res->fd_out += (fd - res->fd_out) * (type >= 3);
	free(name);
	return (false);
}
