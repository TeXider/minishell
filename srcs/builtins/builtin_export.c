/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:43:51 by almighty          #+#    #+#             */
/*   Updated: 2025/12/09 12:51:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static inline bool	compute_export(char *exp, t_var_info *var_info,
	t_env *env)
{
	char	*new_var;

	if (exp[0] == '_' && !is_var_char(exp[1]))
		return (false);
	find_var(exp, var_info, env);
	if (var_info->stat != VAR_INEXISTANT
		&& var_info->operation == TO_EXPORTP)
		return (false);
	if (convert_export_to_var(exp, &new_var, var_info, env))
		return (true);
	if (var_info->stat != VAR_IN_ENVP
		&& ((var_info->stat != VAR_IN_EXPORTP && add_to_exportp(new_var, env))
			|| (var_info->operation != TO_EXPORTP
				&& add_to_envp(new_var, env))))
		return (true);
	if (var_info->stat != VAR_INEXISTANT)
	{
		free(env->exportp[var_info->exportp_index]);
		env->exportp[var_info->exportp_index] = new_var;
		if (var_info->stat == VAR_IN_ENVP)
			env->envp[var_info->envp_index] = new_var;
	}
	return (false);
}

static inline bool	check_export_parsing(char *exp, t_var_info *var_info)
{
	if (!*exp || *exp == '=' || (*exp >= '0' && *exp <= '9'))
		return (true);
	while (is_var_char(*exp))
		exp++;
	var_info->operation = TO_EXPORTP * (!*exp)
		+ TO_ENVP * (*exp == '=')
		+ TO_ENVP_APPND * (*exp == '+');
	return (*exp
		&& (*exp != '=' && !(*exp == '+' && *(exp + 1) == '=')));
}

static inline void	print_export(t_env *env)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < env->exportp_len)
	{
		if (env->exportp[i][0] == '_' && env->exportp[i][1] == '=')
			continue ;
		write(1, "declare -x ", 11);
		j = -1;
		while (is_var_char(env->exportp[i][++j]))
			write(1, env->exportp[i] + j, 1);
		if (env->exportp[i][j] == '=')
		{
			write(1, "=\"", 2);
			while (env->exportp[i][++j])
				write(1, env->exportp[i] + j, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
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
	while (!g_sig && *args)
	{
		if (check_export_parsing(*args, &var_info))
		{
			throw_builtin_error(*args, EXPORT_ERR, INVALID_ID_BERR, env);
			has_error = true;
		}
		else if (!(**args == '_' && (!*(*args + 1) || *(*args + 1) == '='
					|| *(*args + 1) == '+'))
			&& compute_export(*args, &var_info, env))
			return (true);
		args++;
	}
	return (has_error);
}
