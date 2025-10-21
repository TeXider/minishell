/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:31:47 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 08:43:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool	get_arg_expand_len(char **arg, size_t *len, char sep, t_env *env)
{
	char	*var;

	if (get_var(arg, &var, env))
		return (false);
	while (*var && (*var != ' ' || sep != ' '))
	{
		(*len)++;
		var++;
	}
	return (*var == ' ');
}

inline bool	arg_expand(t_get_arg_core *gac, char **argv_ptr, char **arg, t_env *env)
{
	char	*var;

	*arg = gac->curr_str;
	get_var(arg, &var, env);
	while (*var && (*var != ' ' || gac->sep != ' '))
		*((*argv_ptr)++) = *(var++);
	if (*var == ' ')
	{
		gac->curr_str = var;
		gac->in_var = true;
		return (true);
	}
	gac->curr_str = *arg;
	return (false);
}

inline void	redir_expand(char **redir, char *name,
				t_get_redir_name *grn, t_env *env)
{
	char	*var;

	if (get_var(redir, &var, env))
		return ;
	while (*var)
		if (*var != ' ' || grn->sep != ' ')
			name[(grn->i)++] = *(var++);
}

inline bool	get_redir_expand_len(char **redir, size_t *len,
				t_get_redir_name_len *grnl, t_env *env)
{
	char	*var;

	if (get_var(redir, &var, env))
		return (false);
	while (*var)
	{
		if (grnl->sep == ' ' && *var != ' ' && grnl->has_arg
			&& grnl->var_is_sep)
			return (true);
		*len += (*var != ' ' || grnl->sep != ' ');
		grnl->var_is_sep = (grnl->sep == ' ' && *var == ' ');
		grnl->has_arg |= (*var != ' ');
		var++;
	}
	return (false);
}
