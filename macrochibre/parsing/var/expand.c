/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:31:47 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 14:11:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static inline bool	check_var_eq(char **name, char **var)
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

inline void	expand(t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;
	char	*var;
	size_t	i;

	cmdp->str += (*(cmdp->str) == '$');
	i = -1;
	while (!cmdp->saved_str && env->envp[++i])
	{
		var = env->envp[i];
		tmp_str = cmdp->str;
		if (check_var_eq(&tmp_str, &var))
		{
			cmdp->saved_str = tmp_str;
			cmdp->str = var;
		}
	}
}
