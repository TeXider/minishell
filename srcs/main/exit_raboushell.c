/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_raboushell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:39:56 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 15:20:35 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

void	exit_raboushell(t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < env->exportp_len)
		free(env->exportp[i]);
	safe_free((void **) &env->exportp);
	safe_free((void **) &env->envp);
	safe_free_history(&env->get_line_env);
	safe_close(&env->saved_std_in, FD_NULL);
	safe_close(&env->saved_std_out, FD_NULL);
	write(1, "\n\e[38;5;214mShutting down raboushell...\n"RST,
		44 * !env->in_fork);
	close(STD_IN);
	close(STD_OUT);
	exit(env->exit_code);
}