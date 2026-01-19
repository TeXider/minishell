/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_getcwd_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:58:27 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:50 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins_bonus.h"

bool	safe_getcwd(char **dst, t_env *env)
{
	*dst = getcwd(NULL, 0);
	if (!*dst)
	{
		if (errno != EACCES && errno != ENOENT)
		{
			create_error("getcwd()", SYS_ERR
				+ (FATAL_SYS_ERR - SYS_ERR) * (errno == ENOMEM), env);
			return (true);
		}
	}
	return (false);
}
