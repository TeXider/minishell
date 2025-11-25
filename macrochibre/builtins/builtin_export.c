/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 09:43:51 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 10:46:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	replace_var(char **list, size_t index, char *new_var)
{
	free(list[index]);
	list[index] = new_var;
}

static inline bool	compute_export(char *export, t_var_info *var_info,
	t_env *env)
{
	char	*new_var;
	
	if (export[0] == '_' && !is_var_char(export[1]))
		return (false);
	find_var(export, var_info, env);
	if (var_info->stat != VAR_INEXISTANT
		&& var_info->operation == TO_EXPORTP)
		return (false);
	if (convert_export_to_var(export, &new_var, var_info, env))
		return (true);
	if (var_info->stat != VAR_IN_ENVP
		&& ((var_info->stat != VAR_IN_EXPORTP && add_to_exportp(new_var, env))
		|| (var_info->operation != TO_EXPORTP && add_to_envp(new_var, env))))
		return (true);
	if (var_info->stat != VAR_INEXISTANT)
		replace_var(env->exportp, var_info->exportp_index, new_var);
	if (var_info->stat == VAR_IN_ENVP)
		replace_var(env->envp, var_info->envp_index, new_var);
	return (false);
}

static inline bool	check_export_parsing(char *export, t_var_info *var_info)
{
	if (!*export || (*export >= '0' && *export <= '9'))
		return (true);
	while (is_var_char(*export))
		export++;
	var_info->operation = TO_EXPORTP * (!*export)
		+ TO_ENVP * (*export == '=')
		+ TO_ENVP_APPND * (*export == '+');
	return (*export
		&& (*export != '=' && !(*export == '+' && *(export + 1) == '=')));
}

static inline void	print_export(t_env *env)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < env->exportp_len)
	{
		if (env->exportp[i][0] == '_' && env->exportp[i][1] == '=')
			continue ;
		write(1, "declare -x ", 11);
		j = -1;
		while (is_var_char(env->exportp[i][++j]))
			write(1, env->exportp[i] + j, 1);
		if (env->exportp[i][j] == '=')
		{
			write(1, "=\"", 2);
			while (env->exportp[i][++j])
				write(1, env->exportp[i] + j, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
}

bool	builtin_export(char **args, t_env *env)
{
	t_var_info	var_info;
	bool		has_error;
	
	if (!*args)
	{
		print_export(env);
		return (false);
	}
	has_error = false;
	while (*args)
	{
		if (check_export_parsing(*args, &var_info))
		{
			//throw_builtin_error(*args, EXPORT_ERR, INVALID_PARAM_BERR, env);
			write(1, "avoufouinfouinfouin\n", 21);
			has_error = true;
		}
		else if (!(**args == '_'
			&& (!*(*args + 1) || *(*args + 1) == '=' || *(*args + 1) == '+'))
			&& compute_export(*args, &var_info, env))
			return (true);
		args++;
	}
	return (has_error);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	t_env env;
	env.exportp = malloc(sizeof(char *));
	env.exportp[0] = NULL;
	env.exportp_len = 0;
	env.envp = malloc(sizeof(char *));
	env.envp[0] = NULL;
	env.envp_len = 0;
	builtin_export(argv + 1, &env);
	print_export(&env);
	free(env.exportp);
}