/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:54:05 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:14 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins_bonus.h"

void	builtin_env(t_env *env)
{
	size_t	i;

	i = 0;
	while (!g_sig && env->envp[i])
	{
		print_str(env->envp[i]);
		write(1, "\n", 1);
		i++;
	}
}
