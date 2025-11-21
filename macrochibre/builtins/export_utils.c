/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:48:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/21 10:48:48 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	get_new_var(char *export, char **var_dst, t_varop *var_op, t_env *env)
{
	size_t	name_len;
	char	**var_addrs;
	t_varop	var_op;
	
	name_len = var_name_len(export);
	var_op = TO_EXPORT * (!*(export + name_len))
		+ TO_ENV * (*(export + name_len) == '=')
		+ TO_ENV_APPND * (*(export + name_len) == '+');
	if (var_op == TO_ENV_APPND)
	if (safe_challoc(var_dst, name_len + str_len(export + name_len + var_op),
		env))
		return (true);
	export_to_var(export, *var_dst);
}

bool	create_var(char *export, t_env *env)
{
	if (var_op == TO_ENV)
	{
		if (add_var_to_env(new_var, env))
			return (true);
	}
	else if (add_var_to_exportp(*args, var_index, var_stat, env))
		return (true);
	return (false);
}