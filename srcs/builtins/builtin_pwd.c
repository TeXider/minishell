/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:00 by almighty          #+#    #+#             */
/*   Updated: 2025/12/12 10:23:54 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

bool	builtin_pwd(t_env *env)
{
	char	*curr_path;

	if (safe_getcwd(&curr_path, env))
		return (true);
	if (curr_path)
	{
		print_str(curr_path);
		free(curr_path);
	}
	write(1, "\n", 1);
	return (false);
}
