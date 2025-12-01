/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_getcwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:58:27 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 13:25:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

bool	safe_getcwd(char **dst, t_env *env)
{
	*dst = getcwd(NULL, 0);
	if (!*dst)
	{
		create_error("getcwd() :", SYS_ERR, env);
		return (true);
	}
	return (false);
}
