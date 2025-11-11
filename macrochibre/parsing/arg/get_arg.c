/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:44:15 by almighty          #+#    #+#             */
/*   Updated: 2025/11/11 11:02:59 by tpanou-d         ###   ########.fr       */
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
	size_t	len;

	if (get_redir_name_len(cmdp->str, &len, env)
		|| safe_challoc(&cmdp->curr_redir->name, len, env))
		return (true);
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
	return (false);
}
