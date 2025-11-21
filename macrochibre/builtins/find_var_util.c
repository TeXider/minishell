/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:14:27 by almighty          #+#    #+#             */
/*   Updated: 2025/11/21 11:01:45 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_in_exportp(char *var, size_t *var_index, t_env *env)
{
	t_exprt	*curr_exprt;
	size_t	iter_count;
	size_t	cmp_i;

	curr_exprt = env->exportp;
	iter_count = 0;
	while (curr_exprt)
	{
		cmp_i = 0;
		while (var[cmp_i] == curr_exprt->name[cmp_i])
			cmp_i++;
		if (!curr_exprt->name[cmp_i]
			&& (!var[cmp_i] || var[cmp_i] == '=' || var[cmp_i] == '+'))
		{
			*var_index = iter_count;
			return (true);
		}
		curr_exprt = curr_exprt->next;
		iter_count++;
	}
	return (false);
}

static inline bool	is_in_envp(char *var, size_t *var_index, t_env *env)
{
	size_t	envp_i;
	size_t	cmp_i;

	envp_i = 0;
	while (env->envp[envp_i])
	{
		cmp_i = 0;
		while (var[cmp_i] == env->envp[envp_i][cmp_i])
			cmp_i++;
		if (env->envp[envp_i][cmp_i] == '='
			&& (!var[cmp_i] || var[cmp_i] == '=' || var[cmp_i] == '+'))
		{
			*var_index = envp_i;
			return (true);
		}
		envp_i++;
	}
	return (false);
}

t_var_stat	find_var(char *var, size_t *var_index, t_env *env)
{
	if (is_in_envp(var, var_index, env))
		return (VAR_IN_ENV);
	if (is_in_exportp(var, var_index, env))
		return (VAR_IN_EXPORT);
	return (VAR_DOES_NOT_EXIST);
}
