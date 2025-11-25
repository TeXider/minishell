/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_getcwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:58:27 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 14:15:31 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	safe_getcwd(char **dst, t_builtin_err err_origin, t_env *env)
{
	*dst = getcwd(NULL, 0);
	if (!*dst)
	{
		throw_builtin_err(NULL, err_origin, INTERNAL_BERR, env);
		return (true);
	}
	return (false);
}