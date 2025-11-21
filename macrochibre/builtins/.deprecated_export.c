/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:59:47 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/20 09:38:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline int	var_is_export(char *var, char *export, bool *are_equal)
{
	while (*var == *export && is_var_char(*export))
	{
		var++;
		export++;
	}
	if (*export && !is_var_char(*export)
		&& (*export != '=' || (*export == '+' && *(export + 1) != '=')))
		return (true);
	*are_equal = 
}

static inline t_var_stat	search_var_in_list(char *var_name, char **list,
	char ***var_addrs, t_env *env)
{
	bool	are_equal;
	size_t	i;

	i = -1;
	while (list[++i])
	{
		var_eq_res = var_is_export(list[i], var_name, &are_equal);
		if (var_is_export(list[i], var_name))
			return (VAR_ERROR);
		else if (var_eq_res == VAR_EQ)
		{
			*var_addrs = list + i;
			return (VAR_FOUND);
		}
	}
	return (VAR_DOES_NOT_EXIST);
}

static inline t_var_stat	get_var(char *var_name, char ***var_addrs,
	t_env *env)
{
	t_var_stat	var_stat;

	var_stat = search_var_in_list(var_name, env->envp, var_addrs, env);
	if (var_stat == VAR_ERROR)
	{
		create_builtin_error(var_name, EXPORT, INVALID_IDENTIFIER, env);
		return (VAR_ERROR);
	}
	if (var_stat == VAR_FOUND)
		return (VAR_IN_ENV);
	var_stat = search_var_in_list(var_name, env->export, var_addrs, env);
	if (var_stat == VAR_ERROR)
	{
		create_builtin_error(var_name, EXPORT, INVALID_IDENTIFIER, env);
		return (VAR_ERROR);
	}
	if (var_stat == VAR_FOUND)
		return (VAR_IN_EXPORT);
	return (VAR_DOES_NOT_EXIST);
}

static inline bool	get_new_var(char *export, char **new_var, t_varop *var_op,
	t_env *env)
{
	size_t	name_len;
	size_t	val_len;
	char	**var_addrs;
	
	name_len = var_name_len(export);
	*var_op = TO_EXPORT * (!*(export + name_len))
		+ TO_ENV * (*(export + name_len) == '=')
		+ TO_ENV_APPND * (*(export + name_len) == '+');
	val_len = str_len(export + name_len + *var_op);
	if (var_op == TO_ENV_APPND)
		val_len += get_var_len(export, env);
	if (safe_challoc(new_var, name_len + val_len, env))
		return (true);
	new_var[0] = '\0';
	if (*var_op == TO_ENV_APPND
		&& get_var(export, &var_addrs, env) != VAR_DOES_NOT_EXIST)
		cpy_var(*var_addrs, new_var);
	cpy_var(export, *new_var);
	return (false);
}

static inline bool	get_new_list(char ***new_list, t_varop var_op, t_env *env)
{
	if (safe_lalloc(new_list, env->envp_len + (var_op == TO_EXPORT)
			* (env->export_len - env->envp_len) + 1, env))
		return (true);
	if (var_op == TO_EXPORT)
		cpy_list(env->export, *new_list);
	else
		cpy_list(env->envp, *new_list); 
	return (false);
}

static inline bool	create_var(char *export, t_env *env)
{
	t_varop	var_op;
	char	*new_var;
	char	**new_list;
	
	if (get_new_var(export, &new_var, &var_op, env)
		|| get_new_list(&new_list, var_op, env))
	{
		safe_free((void **) &new_var);
		return (true);
	}
	if (var_op == TO_EXPORT)
	{
		new_list[env->export_len] = new_var;
		free(env->export);
		env->export = new_list;
	}
	else
	{
		new_list[env->envp_len] = new_var;
		free(env->envp);
		env->envp = new_list;
	}
	return (false);
}


bool	builtin_export(char **argv, t_env *env)
{
	char		**var_addrs;
	t_var_stat	var_stat;
	
	argv++;
	if (!*argv)
	{
		print_export(env);
		return (false);
	}
	while (*argv)
	{
		var_stat = get_var(*argv, &var_addrs, env);
		if (var_stat == VAR_ERROR)
			return (true);
		if (var_stat == VAR_DOES_NOT_EXIST)
		{
			if (create_var(*argv, env))
				return (true);
		}
		else if (change_var_val(*argv, var_addrs, var_stat, env))
			return (true);
		argv++;
	}
	return (false);
}
