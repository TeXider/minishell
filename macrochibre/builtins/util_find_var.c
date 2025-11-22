/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 09:14:27 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 14:35:26 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	is_var_in_list(char *var, char **list, size_t *var_index)
{
	size_t	list_i;
	size_t	cmp_i;

	list_i = 0;
	while (list[list_i])
	{
		cmp_i = 0;
		while (var[cmp_i] == list[list_i][cmp_i])
			cmp_i++;
		if (list[list_i][cmp_i] == '='
			&& (!var[cmp_i] || var[cmp_i] == '=' || var[cmp_i] == '+'))
		{
			*var_index = list_i;
			return (true);
		}
		list_i++;
	}
	return (false);
}

void	find_var(char *var, size_t *var_index, int *var_info, t_env *env)
{
	if (is_in_envp(var, var_index, env))
		return (VAR_IN_ENV);
	else if (is_in_exportp(var, var_index, env))
		return (VAR_IN_EXPORT);
	else
	{
		*var_index = env->envp_len * ((*var_info & VAR_OPERATION) != TO_EXPORT)
			+ env->exportp_len * ((*var_info & VAR_OPERATION) == TO_EXPORT);
		*var_info |= VAR_STAT & VAR_DOES_NOT_EXIST;
	}
}
