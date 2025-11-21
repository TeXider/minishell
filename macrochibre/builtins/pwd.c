/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:00 by almighty          #+#    #+#             */
/*   Updated: 2025/11/20 12:09:17 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	builtin_pwd(t_env *env)
{
	char	*curr_path;

	curr_path = getcwd(NULL, 0);
	if (!curr_path)
	{
		throw_builtin_error(NULL, PWD_ERR, 0, env);
		return (true);
	}
	print_str(curr_path);
	write(1, "\n", 1);
	free(curr_path);
	return (false);
}