/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_convert_export_to_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:48:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/26 11:21:27 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	appnd_env_var(size_t var_index, char *new_var,
	size_t *new_var_i, t_env *env)
{
	size_t	tmp_i;

	tmp_i = 0;
	while (env->envp[var_index][tmp_i] != '=')
		tmp_i++;
	tmp_i++;
	while (env->envp[var_index][tmp_i])
	{
		new_var[*new_var_i] = env->envp[var_index][tmp_i];
		tmp_i++;
		(*new_var_i)++;
	}
}

static inline size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static inline size_t	compute_var_len(char *export, t_var_info *var_info,
	t_env *env)
{
	size_t	name_len;
	size_t	var_len;

	name_len = 0;
	while (is_var_char(export[name_len]))
		name_len++;
	var_len = name_len;
	if (var_info->stat == VAR_IN_ENVP
		&& var_info->operation == TO_ENVP_APPND)
		var_len += str_len(env->envp[var_info->envp_index] + name_len + 1);
	var_len += str_len(export + name_len
			+ (var_info->operation != TO_EXPORTP)
			+ (var_info->operation == TO_ENVP_APPND));
	return (var_len + (var_info->operation != TO_EXPORTP));
}

bool	convert_export_to_var(char *export, char **var_dst,
	t_var_info *var_info, t_env *env)
{
	bool	has_passed_operator;
	size_t	i;

	if (safe_challoc(var_dst, compute_var_len(export, var_info, env), env))
		return (true);
	has_passed_operator = false;
	i = 0;
	while (*export)
	{
		export += (!has_passed_operator && (*export == '+'));
		(*var_dst)[i] = *export;
		i++;
		if (!has_passed_operator && ((*export == '=')))
		{
			has_passed_operator = true;
			if (var_info->stat == VAR_IN_ENVP
				&& var_info->operation == TO_ENVP_APPND)
				appnd_env_var(var_info->envp_index, *var_dst, &i, env);
		}
		export++;
	}
	(*var_dst)[i] = '\0';
	return (false);
}
