/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:54:05 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:44:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	builtin_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
	{
		print_str(env->envp);
		write(1, "\n", 1);
		i++;
	}
}
