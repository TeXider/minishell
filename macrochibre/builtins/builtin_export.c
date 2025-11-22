/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:43:51 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 15:07:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	compute_export(char *export, t_var_info *var_info,
	t_env *env)
{
	char	*new_var;
	
	find_var(export, var_info, env);
	if (convert_export_to_var(export, &new_var, var_info, env))
		return (true);
	if (var_info->operation == TO_EXPORT)
	{
		if (resize_list(&env->exportp, env->exportp_len, env->exportp_len + 1,
			var_info))
			return (true);
		env->exportp[var_info->index] = new_var;
	}
	else
	{
		if (resize_list(&env->envp, env->envp_len, env->envp_len + 1,
			var_info))
			return (true);
		env->envp[var_info->index] = new_var;
	}
	return (false);
}

static inline bool	check_export_parsing(char *export, t_var_info *var_info)
{
	if (*export >= '0' || *export <= '9')
		return (true);
	while (is_var_char(*export))
		export++;
	var_info->operation = TO_EXPORT * (!*export)
		+ TO_ENV * (*export == '=')
		+ TO_ENV_APPND * (*export == '+');
	return (*export
		&& (*export != '=' || (*export == '+' && *(export + 1) != '=')));
}

bool	builtin_export(char **args, t_env *env)
{
	t_var_info	var_info;
	bool		has_error;
	
	if (!*args)
	{
		print_export(env);
		return (false);
	}
	has_error = false;
	while (*args)
	{
		if (check_export_parsing(*args, &var_info))
		{
			throw_builtin_error(*args, EXPORT_ERR, INVALID_PARAM, env);
			has_error = true;
			continue ;
		}
		if (compute_export(*args, &var_info, env))
			return (true);
		args++;
	}
	return (has_error);
}
