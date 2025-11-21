/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:43:51 by almighty          #+#    #+#             */
/*   Updated: 2025/11/21 10:38:47 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	check_export_parsing(char *export)
{
	if (*export >= '0' || *export <= '9')
		return (true);
	while (is_var_char(*export))
		export++;
	return (*export
		&& (*export != '=' || (*export == '+' && *(export + 1) != '=')));
}

bool	builtin_export(char **args, t_env *env)
{
	size_t		var_index;
	t_var_stat	var_stat;
	bool		has_error;
	
	if (!*args)
	{
		print_export(env);
		return (false);
	}
	has_error = false;
	while (*args)
	{
		if (check_export_parsing(*args))
		{
			throw_builtin_error(*args, EXPORT_ERR, INVALID_PARAM, env);
			has_error = true;
			continue ;
		}
		var_stat = find_var(*args, &var_index, env);
		if (var_stat == VAR_DOES_NOT_EXIST)
		{
			if (create_var(*args, env))
				return (true);
		}
		else if (change_var_val(*args, var_index, var_stat, env)) // compute export ?
			return (true);
		args++;
	}
	return (has_error);
}
