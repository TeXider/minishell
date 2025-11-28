/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_throw_builtin_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:51:42 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:45:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static inline void	print_str_err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

static inline void	print_err_ctxt(char *culprit, t_builtin_err_ctxt err_ctxt)
{
	if (culprit)
	{
		write(2, "`", 1);
		print_str_err(culprit);
		write(2, "': ", 3);
	}
	if (err_ctxt == TOO_MANY_PARAMS_BERR)
		write(2, "too many arguments\n", 19);
	else if (err_ctxt == NUM_ARG_BERR)
		write(2, "numeric argument required\n", 26);
	else if (err_ctxt == INVALID_ID_BERR)
		write(2, "not a valid identifier\n", 23);
	else if (err_ctxt == HOME_NOT_SET_BERR)
		write(2, "HOME not set\n", 13);
	else if (err_ctxt == INTERNAL_BERR)
		perror(NULL);
}

static inline void	print_err_origin(t_builtin_err err)
{
	write(2, RED BOLD, 9);
	if (err == CD_ERR)
		write(2, "cd", 2);
	else if (err == EXIT_ERR)
		write(2, "exit", 4);
	else if (err == EXPORT_ERR)
		write(2, "export", 6);
	else if (err == PWD_ERR)
		write(2, "pwd", 3);
	write(2, ": "RST, 7);
}

void	throw_builin_error(char *culprit, t_builtin_err err,
	t_builtin_err_ctxt err_ctxt, t_env *env)
{
	if (env->err == SYS_ERR)
		return ;
	print_raboushell();
	print_err_origin(err);
	print_err_ctxt(culprit, err_ctxt);
	env->exit_code = 1 + (err_ctxt != INTERNAL_BERR);
}
