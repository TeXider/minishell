/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:40:50 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/25 14:35:00 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	check_new_line(char *arg)
{
	if (*arg != '-')
		return (true);
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
	while (*args && !check_new_line(*args))
	{
		has_new_line = false;
		args++;
	}
	while (*args)
	{
		print_str(*args);
		write(1, " ", *(args + 1) != NULL);
		args++;
	}
	write(1, "\n", has_new_line);
}
