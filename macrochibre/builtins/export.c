/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:59:47 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/18 19:06:46 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	builtin_env(char **argv, t_env *env)
{
	argv++;
	if (!*argv)
	{
		print_export(env);
		return (false);
	}
	while ()
}