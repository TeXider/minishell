/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:40:50 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/19 08:35:59 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **argv)
{
	bool	has_new_line;

	argv++;
	has_new_line = !((*argv)[0] == '-'
			&& (*argv)[1] == 'n'
			&& (*argv)[2] == '\0');
	while (*argv)
	{
		print_str(*argv);
		argv++;
	}
	write(1, "\n", has_new_line);
}
