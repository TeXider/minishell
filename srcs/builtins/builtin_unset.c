/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:30 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 10:09:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
			if ((var_info.stat != VAR_INEXISTANT
					&& remove_from_exportp(var_info.exportp_index, env))
				|| (var_info.stat == VAR_IN_ENVP
					&& remove_from_envp(var_info.envp_index, env)))
				return (true);
		}
		args++;
	}
	return (false);
}
