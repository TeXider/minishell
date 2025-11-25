/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:48:43 by almighty          #+#    #+#             */
/*   Updated: 2025/11/25 09:21:23 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	add_to_envp(char *new_var, t_env *env)
{
	char	**new_envp;
	size_t	i;

	if (safe_lalloc(&new_envp, env->envp_len + 1, env))
		return (true);
	i = -1;
	while (++i < env->envp_len)
		new_envp[i] = env->envp[i];
	new_envp[env->envp_len] = new_var;
	free(env->envp);
	env->envp = new_envp;
	env->envp_len++;
	return (false);
}

bool	remove_from_envp(size_t var_index, t_env *env)
{
	char	**new_envp;
	size_t	i;

	if (safe_lalloc(&new_envp, env->envp_len - 1, env))
		return (true);
	env->envp_len--;
	i = -1;
	while (++i < env->envp_len)
		new_envp[i] = env->envp[i + (i >= var_index)];
	free(env->envp[var_index]);
	free(env->envp);
	env->envp = new_envp;
	return (false);
}

// int	main()
// {

// 	t_env env;
// 	env.envp = malloc(sizeof(char *) * 4);
// 	env.envp[3] = NULL;
// 	env.envp[0] = "bousiller="; env.envp[1] = "kiri=123456"; env.envp[2] = "fort=rin tin tin ";
// 	env.envp_len = 3;
// 	char input[256];
// 	while (true)
// 	{
// 		int rd = read(0, input, 256);
// 		input[rd] = '\0';
// 		char *var = malloc(sizeof(char) * 256);
// 		int i;
// 		for (i = 2; input[0] != 'r' && input[i] != ' '; i++)
// 			var[i] = input[i];
// 		var[i] = '\0';
// 		if (input[0] == 'r')
// 			free(var);
// 		if (*input == 'r')
// 			remove_from_envp((size_t) atoi(input + i + 2), &env);
// 		else
// 			insert_in_envp(var, atoi(input + i + 2), &env);
// 		for (size_t j = 0; j < env.envp_len; j++)
// 		{
// 			for (int k = 0; env.envp[j][k]; k++)
// 				write(1, env.envp[j] + k, 1);
// 			write(1, "\n", 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// }