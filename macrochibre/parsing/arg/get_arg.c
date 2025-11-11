/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:44:15 by almighty          #+#    #+#             */
/*   Updated: 2025/11/11 10:37:50 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static inline void	actualize_strs(t_get_arg_core *gac, char **arg)
{
	if (!gac->in_var)
		*arg = gac->curr_str;
	else if (!*(gac->curr_str))
	{
		gac->in_var = false;
		gac->curr_str = *arg;
		gac->curr_str++;
	}
}

static inline size_t	arg_len(char *curr_str, t_get_arg_core *gac, t_env *env)
{
	size_t	len;

	len = 0;
	while ((!is_end_of_arg(*curr_str, gac->sep)) || (gac->in_var
			&& (gac->sep != ' ' || *curr_str != ' ')))
	{
		if (!gac->in_var && ((gac->sep == ' ' && is_quote(*curr_str))
				|| *curr_str == gac->sep))
			set_sep(&gac->sep, *curr_str);
		else if (!gac->in_var && is_var(curr_str, gac->sep))
		{
			if (get_arg_expand_len(&curr_str, &len, gac->sep, env))
				return (len);
		}
		else
			len++;
		curr_str++;
	}
	return (len);
}

static inline void	get_arg_core(t_get_arg_core *gac, char *argv_ptr,
			char **arg, t_env *env)
{
	while ((!is_end_of_arg(*(gac->curr_str), gac->sep))
		|| (gac->in_var && (gac->sep != ' ' || *(gac->curr_str) != ' ')))
	{
		if (!gac->in_var && ((gac->sep == ' '
					&& is_quote(*(gac->curr_str)))
				|| *(gac->curr_str) == gac->sep))
			set_sep(&gac->sep, (*gac->curr_str));
		else if (!gac->in_var && is_var(gac->curr_str, gac->sep))
		{
			if (arg_expand(gac, &argv_ptr, arg, env))
				break ;
		}
		else
			*(argv_ptr++) = *(gac->curr_str);
		gac->curr_str++;
	}
	if (gac->in_var)
		skip_spaces(&gac->curr_str);
}

bool	get_arg(t_cmd_parsing *cmdp, t_env *env)
{
	t_get_arg_core	gac;
	size_t			len;

	gac.curr_str = *arg;
	gac.sep = ' ';
	gac.in_var = false;
	while (!is_end_of_arg(**arg, gac.sep))
	{
		len = arg_len(gac.curr_str, &gac, env);
		if (len && safe_challoc(res->argv + *arg_i, len, env))
			return (true);
		get_arg_core(&gac, res->argv[*arg_i], arg, env);
		actualize_strs(&gac, arg);
		res->argv[*arg_i + 1] = NULL;
		*arg_i += (len != 0);
	}
	return (false);
}
