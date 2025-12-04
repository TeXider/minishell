/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:35:05 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 09:19:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"
#include <signal.h>

static void	sig_int(int sig)
{
	(void) sig;
	g_sig = SIGNAL_INT;
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_int;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigint(t_env *env)
{
	write(1, "^C\n", 3 * !env->in_fork);
	set_exit_code(130, env);
	g_sig = 0;
}