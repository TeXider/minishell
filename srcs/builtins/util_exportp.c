/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exportp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 15:56:03 by almighty          #+#    #+#             */
/*   Updated: 2025/11/26 11:20:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline size_t	is_alph_order(char *var_str, char *exportp_str)
{
	size_t	i;

	if (!exportp_str)
		return (true);
	i = 0;
	while (is_var_char(exportp_str[i]) && is_var_char(var_str[i])
		&& exportp_str[i] == var_str[i])
		i++;
	return (!is_var_char(var_str[i]) || exportp_str[i] >= var_str[i]);
}

bool	add_to_exportp(char *new_var, t_env *env)
{
	char	**new_exportp;
	size_t	new_index;
	bool	is_var_placed;
	size_t	i;

	if (safe_lalloc(&new_exportp, env->exportp_len + 1, env))
		return (true);
	new_index = env->exportp_len;
	is_var_placed = false;
	i = -1;
	while (++i < env->exportp_len)
	{
		if (!is_var_placed && is_alph_order(new_var, env->exportp[i]))
		{
			new_index = i;
			is_var_placed = true;
		}
		new_exportp[i + is_var_placed] = env->exportp[i];
	}
	new_exportp[new_index] = new_var;
	free(env->exportp);
	env->exportp = new_exportp;
	env->exportp_len++;
	return (false);
}

bool	remove_from_exportp(size_t var_index, t_env *env)
{
	char	**new_exportp;
	size_t	i;

	if (safe_lalloc(&new_exportp, env->exportp_len - 1, env))
		return (true);
	env->exportp_len--;
	i = -1;
	while (++i < env->exportp_len)
		new_exportp[i] = env->exportp[i + (i >= var_index)];
	free(env->exportp[var_index]);
	free(env->exportp);
	env->exportp = new_exportp;
	return (false);
}
