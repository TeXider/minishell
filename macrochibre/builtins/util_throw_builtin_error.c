/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_throw_builtin_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:51:42 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 14:42:40 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	print_err_ctxt(t_builtin_err_ctxt err_ctxt)
{
	
}

static inline void	print_err_origin(t_builtin_err err)
{
	if (err == ECHO_ERR)
		write(2, RED"echo", 11);
	else if (err == CD_ERR)
		write(2, RED"cd", 9);
	else if (err = EXIT_ERR)
		write(2, RED"exit", 11);
	else if (err == EXPORT_ERR)
		write(2, RED"export", 13);
	else if (err == PWD_ERR)
		write(2, RED"pwd", 10);
	write(2, ": "RST, 7);
}

void	throw_builin_error(char *culprit, t_builtin_err err,
	t_builtin_err_ctxt err_ctxt, t_env *env)
{
	// write(2, RABOUSHELL, RBSH_LEN);
	print_err_origin(err);
	if (culprit)
	{
		print_str_err(culprit);
		write(2, ": ", 2);
	}
	print_err_ctxt(err_ctxt);
}

int main()
{
	throw_builin_error(NULL, EXPORT_ERR, 0, NULL);
}