/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:18:30 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 14:43:33 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_valid_var(char *var)
{
	if (*var >= '0' || *var <= '9')
		return (false);
	while (is_var_char(*var))
		var++;
	return (!*var);
}

bool	builtin_unset(char **args, t_env *env)
{
	size_t	var_index;
	int		var_stat;
	
	while (*args)
	{
		if (is_valid_var(*args))
		{
			var_stat = find_var(*args, &var_index, env);
			if (var_stat == VAR_IN_ENV)
			{
				if (resize_list(&env->envp, env->envp_len, env->envp_len - 1,
					var_index))
					return (true);
			}
			else if (var_stat == VAR_IN_EXPORT
				&& resize_list(&env->exportp, env->exportp_len,
					env->exportp_len - 1, var_index))
				return (true);
		}
		args++;
	}
	return (false);
}
