/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:14:55 by almighty          #+#    #+#             */
/*   Updated: 2025/12/19 11:37:33 by almighty         ###   ########.fr       */
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

static inline void	set_special_culprit(char *culprit, t_env *env)
{
	if (*culprit == '\'')
		env->culprit = "`''";
	else if (*culprit == '"')
		env->culprit = "`\"'";
	else if (*culprit == '>')
		env->culprit = "`>'";
	else if (*culprit == '<')
		env->culprit = "`<'";
	else if (*culprit == '|' && *(culprit + 1) != '|')
		env->culprit = "`|'";
	else if (*culprit == '|' && *(culprit + 1) == '|')
		env->culprit = "`||'";
	else if (*culprit == '&')
		env->culprit = "`&&'";
	else if (*culprit == '(')
		env->culprit = "`('";
	else if (*culprit == ')')
		env->culprit = "`)'";
	else if (*culprit == '\n')
		env->culprit = "`newline'";
	else
		env->culprit = culprit;
}

void	create_error(char *culprit, t_err err, t_env *env)
{
	if (env->free_culprit)
	{
		safe_free((void **) &env->culprit);
		env->free_culprit = false;
	}
	env->err = err;
	if (err == UNCLOSED_QUOTES_ERR || err == UNEXPECTED_TOKEN_ERR)
		set_special_culprit(culprit, env);
	else
		env->culprit = culprit;
	env->end_of_raboushell = (err == FATAL_SYS_ERR || err == TERM_ERR);
	create_exit_code(env);
}
