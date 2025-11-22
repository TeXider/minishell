/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:43:51 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 14:38:33 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	compute_export(char *export, int var_info, t_env *env)
{
	size_t	var_index;
	char	*new_var;
	
	var_info |= VAR_STAT & find_var(export, &var_index, env);
	new_var = convert_export_to_var(export, var_info, var_index, env);
	if (!new_var)
		return (true);
	if ((var_info & VAR_OPERATION) == TO_EXPORT)
	{
		if (resize_list(&env->exportp, env->exportp_len, env->exportp_len + 1,
			var_index))
			return (true);
		env->exportp[var_index] = new_var;
	}
	else
	{
		if (resize_list(&env->envp, env->envp_len, env->envp_len + 1,
			var_index))
			return (true);
		env->envp[var_index] = new_var;
	}
	return (false);
}

static inline bool	check_export_parsing(char *export, int *var_info)
{
	if (*export >= '0' || *export <= '9')
		return (true);
	while (is_var_char(*export))
		export++;
	*var_info |= VAR_OPERATION & (TO_EXPORT * (!*export)
		+ TO_ENV * (*export == '=')
		+ TO_ENV_APPND * (*export == '+'));
	return (*export
		&& (*export != '=' || (*export == '+' && *(export + 1) != '=')));
}

bool	builtin_export(char **args, t_env *env)
{
	int		var_info;
	bool	has_error;
	
	if (!*args)
	{
		print_export(env);
		return (false);
	}
	var_info = 0;
	has_error = false;
	while (*args)
	{
		if (check_export_parsing(*args, &var_info))
		{
			throw_builtin_error(*args, EXPORT_ERR, INVALID_PARAM, env);
			has_error = true;
			continue ;
		}
		if (compute_export(*args, var_info, env))
			return (true);
		args++;
	}
	return (has_error);
}
