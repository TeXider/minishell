/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:30 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:34 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins_bonus.h"

static inline bool	is_valid_var(char *var)
{
	if ((*var >= '0' && *var <= '9') || (*var == '_' && !*(var + 1)))
		return (false);
	while (is_var_char(*var))
		var++;
	return (!*var);
}

bool	builtin_unset(char **args, t_env *env)
{
	t_var_info	var_info;

	while (!g_sig && *args)
	{
		if (is_valid_var(*args))
		{
			find_var(*args, &var_info, env);
			if ((var_info.stat != VAR_NONEXISTENT
					&& remove_from_exportp(var_info.exportp_index, env))
				|| (var_info.stat == VAR_IN_ENVP
					&& remove_from_envp(var_info.envp_index, env)))
				return (true);
		}
		args++;
	}
	return (false);
}
