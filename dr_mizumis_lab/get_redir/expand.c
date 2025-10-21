/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:31:47 by almighty          #+#    #+#             */
/*   Updated: 2025/10/02 11:42:42 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	redir_expand(char **redir, char *name,
				t_get_redir_name *grn, t_env *env)
{
	t_var	var;
	size_t	i;

	if (get_var(redir, &var, env))
		return ;
	i = -1;
	while (var.val[++i])
		if (var.val[i] != ' ' || grn->sep != ' ')
			name[(grn->i)++] = var.val[i];
}

inline bool	get_redir_expand_len(char **redir, size_t *len,
				t_get_redir_name_len *grnl, t_env *env)
{
	t_var	var;
	size_t	i;

	if (get_var(redir, &var, env))
		return (false);
	i = -1;
	while (var.val[++i])
	{
		if (grnl->sep == ' ' && var.val[i] != ' ' && grnl->has_arg
			&& grnl->var_is_sep)
			return (true);
		*len += (var.val[i] != ' ' || grnl->sep != ' ');
		grnl->var_is_sep = (grnl->sep == ' ' && var.val[i] == ' ');
		grnl->has_arg |= (var.val[i] != ' ');
	}
	return (false);
}
