/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:48:43 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:44:43 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

bool	add_to_envp(char *new_var, t_env *env)
{
	char	**new_envp;
	size_t	i;

	if (safe_lalloc(&new_envp, env->envp_len + 1, env))
		return (true);
	i = -1;
	while (++i < env->envp_len)
		new_envp[i] = env->envp[i];
	new_envp[env->envp_len] = new_var;
	free(env->envp);
	env->envp = new_envp;
	env->envp_len++;
	return (false);
}

bool	remove_from_envp(size_t var_index, t_env *env)
{
	char	**new_envp;
	size_t	i;

	if (safe_lalloc(&new_envp, env->envp_len - 1, env))
		return (true);
	env->envp_len--;
	i = -1;
	while (++i < env->envp_len)
		new_envp[i] = env->envp[i + (i >= var_index)];
	free(env->envp[var_index]);
	free(env->envp);
	env->envp = new_envp;
	return (false);
}
