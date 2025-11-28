/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:26:23 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:40:03 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUITLINS_H

# include "raboushell.h"

typedef enum e_builtin_err
{
	ECHO_ERR,
	CD_ERR,
	PWD_ERR,
	EXPORT_ERR,
	UNSET_ERR,
	ENV_ERR,
	EXIT_ERR
}	t_builtin_err;

typedef enum e_builtin_err_ctxt
{
	TOO_MANY_PARAMS_BERR,
	NUM_ARG_BERR,
	INVALID_ID_BERR,
	HOME_NOT_SET_BERR,
	INTERNAL_BERR,
}	t_builtin_err_ctxt;


typedef struct s_var_info
{
	char	stat;
	char	operation;
	size_t	envp_index;
	size_t	exportp_index;
}	t_var_info;

/* BUILTINS */

void	builtin_echo(char **args);
void	builtin_env(t_env *env);
bool	builtin_cd(char **args, t_env *env);
bool	builtin_exit(char **args, t_env *env);
bool	builtin_export(char **args, t_env *env);
bool	builtin_pwd(t_env *env);
bool	builtin_unset(char **args, t_env *env);

/* UTILS */

bool	convert_export_to_var(char *exp, char **var_dst, t_var_info *var_info,
			t_env *env);
bool	add_to_envp(char *new_var, t_env *env);
bool	remove_from_envp(size_t var_index, t_env *env);
bool	add_to_exportp(char *new_var, t_env *env);
bool	remove_from_exportp(size_t var_index, t_env *env);
void	find_var(char *var, t_var_info *var_info, t_env *env);
void	throw_builin_error(char *culprit, t_builtin_err err,
			t_builtin_err_ctxt err_ctxt, t_env *env);

# endif