/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_safe_getcwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:58:27 by almighty          #+#    #+#             */
/*   Updated: 2025/11/26 11:22:34 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	safe_getcwd(char **dst, t_env *env)
{
	*dst = getcwd(NULL, 0);
	if (!*dst)
	{
		create_error(NULL, SYS_ERR, env);
		return (true);
	}
	return (false);
}
