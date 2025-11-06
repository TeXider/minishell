/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:31:47 by almighty          #+#    #+#             */
/*   Updated: 2025/11/06 16:44:02 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_var_eq(char **str, char **var)
{
	bool	res;

	res = true;
	while (is_var_char(**str))
	{
		res &= (**var == **str);
		(*var) += (**var != '=');
		(*str)++;
	}
	res &= (**var == '=');
	(*var)++;
	return (res);
}

void	expand(t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;
	char	*var;
	size_t	i;

	cmdp->str += (*(cmdp->str) == '$');
	tmp_str = cmdp->str;
	i = -1;
	while (!cmdp->saved_str && env->envp[++i])
	{
		var = env->envp[i];
		cmdp->str = tmp_str;
		if (check_var_eq(&cmdp->str, &var))
		{
			if (!*var)
				return ;
			cmdp->saved_str = cmdp->str;
			cmdp->str = var;
			cmdp->in_expand = true;
		}
	}
}

inline void	exit_expand(t_cmd_parsing *cmdp)
{
	cmdp->str = cmdp->saved_str;
	cmdp->in_expand = false;
}