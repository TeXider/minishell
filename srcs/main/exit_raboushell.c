/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_raboushell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:39:56 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 12:44:03 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

void	exit_raboushell(t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < env->exportp_len)
		free(env->exportp[i]);
	free(env->exportp);
	free(env->envp);
	clear_history(&env->get_line_env);
	exit(env->exit_code);
}