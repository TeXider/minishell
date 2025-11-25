/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_find_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:14:27 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 09:30:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	var_eq(char *var1, char *var2)
{
	size_t	i;

	i = 0;
	while (is_var_char(var1[i]) && is_var_char(var2[i]) && var1[i] == var2[i])
		i++;
	return ((!var1[i] || var1[i] == '=' || var1[i] == '+')
		&& (!var2[i] || var2[i] == '=' || var2[i] == '+'));
}

void	find_var(char *var, t_var_info *var_info, t_env *env)
{
	bool	found_in_envp;
	bool	found_in_exportp;
	size_t	envp_i;
	size_t	exportp_i;

	found_in_envp = false;
	found_in_exportp = false;
	envp_i = 0;
	exportp_i = 0;
	while ((!found_in_exportp && exportp_i < env->exportp_len)
		|| (!found_in_envp && envp_i < env->envp_len))
	{
		found_in_envp |= (envp_i < env->envp_len && !found_in_envp
			&& var_eq(env->envp[envp_i], var));
		found_in_exportp |= (exportp_i < env->exportp_len && !found_in_exportp
			&& var_eq(env->exportp[exportp_i], var));
		envp_i += (!found_in_envp && envp_i < env->envp_len);
		exportp_i += (!found_in_exportp && exportp_i < env->exportp_len);
	}
	var_info->stat = VAR_INEXISTANT
		+ VAR_IN_EXPORTP * (found_in_exportp && !found_in_envp)
		+ VAR_IN_ENVP * (found_in_envp);
	var_info->envp_index = envp_i;
	var_info->exportp_index = exportp_i;
}
