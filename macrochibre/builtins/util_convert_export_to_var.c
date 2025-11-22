/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:48:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 12:08:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	appnd_env_var(size_t var_index, char *new_var,
	size_t *new_var_i, t_env *env)
{
	size_t	tmp_i;

	tmp_i = 0;
	while (env->envp[var_index][tmp_i] != '=')
		tmp_i++;
	tmp_i++;
	while (env->envp[var_index][tmp_i])
	{
		new_var[*new_var_i] = env->envp[var_index][tmp_i];
		tmp_i++;
		(*new_var_i)++;
	}
}

static inline size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static inline size_t	compute_var_len(char *export, int var_info,
	size_t var_index, t_env *env)
{
	size_t	name_len;
	size_t	var_len;

	name_len = 0;
	while (is_var_char(export[name_len]))
		name_len++;
	var_len = name_len;
	if ((var_info & VAR_STAT) == VAR_IN_ENV
		&& (var_info & VAR_OPERATION) == TO_ENV_APPND)
		var_len += str_len(env->envp[var_index] + name_len + 1);
	var_len += str_len(export + name_len
		+ ((var_info & VAR_OPERATION) != TO_EXPORT)
		+ ((var_info & VAR_OPERATION) == TO_ENV_APPND));
	printf("%zu\n", var_len + 1);
	return (var_len + ((var_info & VAR_OPERATION) != TO_EXPORT));
}

char	*convert_export_to_var(char *export, int var_info, size_t var_index,
	t_env *env)
{
	char	*new_var;
	bool	has_passed_operator;
	size_t	i;

	if (safe_challoc(&new_var,
		compute_var_len(export, var_info, var_index, env), env))
		return (NULL);
	has_passed_operator = false;
	i = 0;
	while (*export)
	{
		export += (!has_passed_operator && (*export == '+'));
		new_var[i] = *export;
		i++;
		if (!has_passed_operator && ((*export == '=')))
		{
			has_passed_operator = true;
			if ((var_info & VAR_STAT) == VAR_IN_ENV
				&& (var_info & VAR_OPERATION) == TO_ENV_APPND)
				appnd_env_var(var_index, new_var, &i, env);
		}
		export++;
	}
	new_var[i] = '\0';
	return (new_var);
}

int	main(int argc, char **argv)
{
	(void) argc;

	t_env env;
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller="; env.envp[1] = "kiri=123456"; env.envp[2] = "fort=rin tin tin ";
	env.err = 0;
	char *var = convert_export_to_var(argv[1], atoi(argv[2]), atoi(argv[3]), &env);
	if (!var)
		write(1, "wadahelli", 10);
	else
		while (*var)
			write(1, var++, 1);
	write(1, "\n", 1);
}