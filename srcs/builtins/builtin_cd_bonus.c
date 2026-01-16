/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:10:23 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 14:57:11 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static inline void	free_set_dirs_data(char **export_args, char *new_dir)
{
	if (new_dir)
		free(new_dir);
	if (*export_args)
		free(*export_args);
	if (*(export_args + 1))
		free(*(export_args + 1));
	free(export_args);
}

static inline bool	create_cd_var(char *name, char *val,
	char **var_dst, t_env *env)
{
	size_t	name_i;
	size_t	val_i;

	if (!val)
		return (false);
	name_i = 0;
	val_i = 0;
	while (name[name_i] || val[val_i])
	{
		name_i += (name[name_i] != '\0');
		val_i += (val[val_i] != '\0');
	}
	if (safe_challoc(var_dst, name_i + val_i + 1, env))
		return (true);
	name_i = 0;
	val_i = 0;
	while (name[name_i] || val[val_i])
	{
		(*var_dst)[name_i + val_i + (!name[name_i])] = name[name_i]
			+ val[val_i] * (!name[name_i]);
		val_i += (!name[name_i] && val[val_i] != '\0');
		name_i += (name[name_i] != '\0');
	}
	(*var_dst)[name_i] = '=';
	return (false);
}

static inline bool	get_new_dir(char *dir, char **new_dir_dst, t_env *env)
{
	size_t	i;

	if (!dir)
	{
		i = -1;
		while (++i < env->envp_len)
		{
			if (env->envp[i][0] == 'H'
				&& env->envp[i][1] == 'O'
				&& env->envp[i][2] == 'M'
				&& env->envp[i][3] == 'E'
				&& env->envp[i][4] == '=')
			{
				*new_dir_dst = env->envp[i] + 5;
				return (false);
			}
		}
		throw_builtin_error(NULL, CD_ERR, HOME_NOT_SET_BERR, env);
		return (true);
	}
	*new_dir_dst = dir;
	return (false);
}

static inline void	set_dirs(char *dir, char *old_dir, char *new_dir,
	t_env *env)
{
	char	**export_args;

	if (get_new_dir(dir, &new_dir, env)
		|| safe_lalloc(&export_args, 2, env))
		return ;
	*export_args = NULL;
	*(export_args + 1) = NULL;
	if (chdir(new_dir))
	{
		free(export_args);
		throw_builtin_error(new_dir, CD_ERR, INTERNAL_BERR, env);
		return ;
	}
	if (create_cd_var("OLDPWD", old_dir, export_args + 1, env))
	{
		free_set_dirs_data(export_args, NULL);
		return ;
	}
	if (!safe_getcwd(&new_dir, env)
		&& !create_cd_var("PWD", new_dir, export_args, env)
		&& *export_args)
		builtin_export(export_args, env);
	free_set_dirs_data(export_args, new_dir);
}

void	builtin_cd(char **args, t_env *env)
{
	char	*old_dir;
	char	*new_dir;

	if (*args && *(args + 1))
	{
		throw_builtin_error(NULL, CD_ERR, TOO_MANY_PARAMS_BERR, env);
		return ;
	}
	if (!safe_getcwd(&old_dir, env))
	{
		new_dir = NULL;
		set_dirs(*args, old_dir, new_dir, env);
	}
	if (old_dir)
		free(old_dir);
}
