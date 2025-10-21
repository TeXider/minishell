/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:36:46 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 07:57:46 by almighty         ###   ########.fr       */
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
