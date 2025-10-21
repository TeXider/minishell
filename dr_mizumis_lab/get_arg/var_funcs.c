/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 08:00:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

inline bool	is_var(char *str, char sep)
{
	return (*str == '$' && sep != '\'' && is_var_char(*(str + 1)));
}

static inline bool check_var_eq(char **name, char **var)
{
	bool	res;

	res = true;
	while (is_var_char(**name))
	{
		res &= (**var == **name);
		(*var) += (**var != '=');
		(*name)++;
	}
	(*name) -= 1;
	res &= (**var == '=');
	(*var)++;
	return (res);
}

bool	get_var(char **name, char **res, t_env *env)
{
	size_t	i;
	char	*tmp_name;

	(*name) += (**name == '$');
	i = -1;
	while (env->envp[++i])
	{
		*res = env->envp[i];
		tmp_name = *name;
		if (check_var_eq(&tmp_name, res))
		{
			*name = tmp_name;
			return (false);
		}
	}
	*name = tmp_name;
	*res = env->empty_string;
	return (true);
}
	// len = 0;
	// while ((*name)[len] && is_var_char((*name)[len]))
	// 	len++;
	// i = -1;
