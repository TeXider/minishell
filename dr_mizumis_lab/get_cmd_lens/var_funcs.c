/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2025/09/23 09:36:16 by almighty         ###   ########.fr       */
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

bool	check_var_empty(char **var_str, t_env *env)
{
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	i = -1;
	while (var.val[++i])
		if (var.val[i] != ' ')
			return (false);
	return (true);
}

bool	check_ambiguous_var(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
			&& var.val[i + 1] != ' ')
			return (true);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (false);
}

int	check_var_validity(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (1);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
			&& var.val[i + 1] != ' ')
			return (2);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (!has_arg);
}
