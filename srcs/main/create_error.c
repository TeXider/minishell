/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:14:55 by almighty          #+#    #+#             */
/*   Updated: 2025/12/08 12:47:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void	create_exit_code(t_env *env)
{
	env->exit_code = 2 * (env->err == UNCLOSED_QUOTES_ERR
			|| env->err == UNEXPECTED_TOKEN_ERR)
		+ 126 * (env->err == CMD_NOT_EXEC_ERR)
		+ 127 * (env->err == CMD_FILE_NOT_FOUND_ERR
			|| env->err == CMD_NOT_FOUND_ERR);
	env->exit_code += !(env->exit_code);
	set_exit_code(env->exit_code, env);
}

void	create_error(char *culprit, t_err err, t_env *env)
{
	size_t	i;

	env->err = err;
	if (err == UNCLOSED_QUOTES_ERR || err == UNEXPECTED_TOKEN_ERR)
	{
		env->culprit[0] = *culprit;
		i = 1;
	}
	else
	{
		i = -1;
		while (++i < CULPRIT_LENGTH && culprit[i])
			env->culprit[i] = culprit[i];
		if (i == CULPRIT_LENGTH && culprit[i])
		{
			env->culprit[i - 1] = '\0';
			env->culprit[i - 2] = '.';
			env->culprit[i - 3] = '.';
			env->culprit[i - 4] = '.';
		}
	}
	env->culprit[i] = '\0';
	env->end_of_raboushell = (err == FATAL_SYS_ERR || err == TERM_ERR);
	create_exit_code(env);
}
