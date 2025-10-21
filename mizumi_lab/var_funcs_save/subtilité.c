/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtilité.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:05:59 by almighty          #+#    #+#             */
/*   Updated: 2025/10/03 08:30:52 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_env
{
	char	**envp;
}	t_env;

bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

bool check_var_eq(char **name, char **var)
{
	bool	res;

	res = true;
	while (is_var_char(**name))
	{
		res &= (**var == **name);
		(*var) += (**var != '=');
		(*name)++;
	}
	(*name) -= 1;
	res &= (**var == '=');
	(*var)++;
	return (res);
}

bool	get_var(char **name, char **res, t_env *env)
{
	size_t	i;
	char	*tmp_name;

	(*name) += (**name == '$');
	i = -1;
	while (env->envp[++i])
	{
		*res = env->envp[i];
		tmp_name = *name;
		if (check_var_eq(&tmp_name, res))
		{
			*name = tmp_name;
			return (false);
		}
	}
	*res = NULL;
	return (true);
}

void	print_str(char *str)
{
	if (!str)
	{
		write(1, "(nil)\n", 6);
		return ;
	}
	str--;
	while (*(++str))
		write(1, str, 1);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int		rd;
	char	input[500];
	char	*tmp_input;
	char	*var;
	t_env	env;

	env.envp = malloc(sizeof(char *) * argc);
	env.envp[argc - 1] = NULL;
	for (size_t i = 1; i < (size_t)argc; i++)
		env.envp[i - 1] = argv[i];
	while (true)
	{
		rd = read(0, input, 499);
		if (rd == -1 || !rd)
		{
			free(env.envp);
			return (1);
		}
		input[rd] = '\0';
		tmp_input = input;
		get_var(&tmp_input, &var, &env);
		print_str(var);
		print_str(tmp_input);
	}
}