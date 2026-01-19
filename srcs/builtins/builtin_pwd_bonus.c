/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:00 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:32 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins_bonus.h"

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
