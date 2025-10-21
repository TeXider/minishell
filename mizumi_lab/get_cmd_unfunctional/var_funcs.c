/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2025/10/01 07:36:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

int	get_var(char **name, t_var *res, t_env *env)
{
	size_t	len;
	size_t	i;

	(*name) += (**name == '$');
	len = 0;
	while ((*name)[len] && is_var_char((*name)[len]))
		len++;
	i = -1;
	while (++i < env->envp_len)
	{
		if (str_eq(*name, env->envp[i]->name, len))
		{
			*name += len - 1;
			res->name = env->envp[i]->name;
			res->val = env->envp[i]->val;
			return (0);
		}
	}
	*name += len - 1;
	res->name = NULL;
	res->val = NULL;
	return (1);
}

