/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:10:23 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 11:33:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	create_cd_var(char *name, char *val,
	char **var_dst, t_env *env)
{
	size_t	name_i;
	size_t	val_i;
	
	if (safe_challoc(var_dst, str_len(name) + str_len(val) + 1, env))
		return (true);
	name_i = 0;
	val_i = 0;
	while (name[name_i] || val[val_i])
	{
		(*var_dst)[name_i + val_i + !(name[name_i])] = name[name_i]
				+ val[val_i] * (!name[name_i]);
		name_i += (name[name_i] != '\0');
		val_i += (name[val_i] != '\0');
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
		throw_builtin_error("HOME", CD_ERR, VAR_NOT_SET_BERR, env);
		return (true);
	}
	*new_dir_dst = dir;
	return (false);
}

static inline bool set_dirs(char *dir, char *old_dir, t_env *env)
{
	char	*new_dir;
	char	**export_args;
	bool	err;

	if (get_new_dir(dir, &new_dir, env)
		|| safe_lalloc(&export_args, 2, env))
		return (true);
	err = false;
	*export_args = NULL;
	*(export_args + 1) = NULL;
	if (create_cd_var("OLD_PWD", old_dir, export_args, env)
		|| create_cd_var("PWD", new_dir, export_args + 1, env)
		|| builtin_export(export_args, env))
		err = true;
	if (*export_args)
		free(*export_args);
	if (*(export_args + 1))
		free(*(export_args + 1));
	free(export_args);
	return (err);
}

bool	builtin_cd(char **args, t_env *env)
{
	char	*old_dir;
	char	*new_dir;

	if (*args && *(args + 1))
	{
		throw_builtin_error(NULL, CD_ERR, TOO_MANY_PARAMS_BERR, env);
		return (true);
	}
	old_dir = getcwd(NULL, 0);
	if (!old_dir)
	{
		throw_builtin_err(NULL, CD_ERR, INTERNAL_BERR, env);
		return (true);
	}
	if (set_dirs(*args, old_dir, env))
	{
		free(old_dir);
		return (true);
	}
	free(old_dir);
	if (chdir(new_dir))
	{
		throw_builtin_err(NULL, CD_ERR, INTERNAL_BERR, env);
		return (true);
	}
	return (false);
}
