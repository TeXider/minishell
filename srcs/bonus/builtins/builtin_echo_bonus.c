/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:40:50 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:12 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins_bonus.h"

static inline bool	check_no_new_line_option(char *arg)
{
	if (*arg != '-')
		return (false);
	arg++;
	while (*arg == 'n')
		arg++;
	return (!*arg && *(arg - 1) != '-');
}

void	builtin_echo(char **args)
{
	bool	has_new_line;

	if (!*args)
	{
		write(1, "\n", 1);
		return ;
	}
	has_new_line = true;
	while (!g_sig && *args && check_no_new_line_option(*args))
	{
		has_new_line = false;
		args++;
	}
	while (!g_sig && *args)
	{
		print_str(*args);
		write(1, " ", *(args + 1) != NULL);
		args++;
	}
	write(1, "\n", has_new_line && !g_sig);
}
