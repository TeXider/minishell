/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:40:50 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/18 19:04:15 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **argv)
{
	bool	has_new_line;

	has_new_line = true;
	while (*(argv++))
	{
		if (has_new_line
			&& (*argv)[0] == '-'
			&& (*argv)[1] == 'n'
			&& (*argv)[2] == '\0')
			has_new_line = false;
		else
			print_str(*argv);
	}
	write(1, "\n", has_new_line);
}
