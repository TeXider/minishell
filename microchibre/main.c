/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/10/16 10:03:13 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	init_env(t_env *env, char **envp)
{
	env->envp = envp;
	env->empty_string[0] = '\0';
	env->empty_list[0] = NULL;
	env->empty_list[1] = NULL;
	env->err = 0;
}

static inline bool	get_input(char *input, t_env *env)
{
	ssize_t	nbytes;

	write(1, "microchibre   $ ", 15);
	nbytes = read(0, input, 499);
	if (nbytes == -1)
		return (create_error("read()", SYS_ERR, env));
	input[nbytes] = '\0';
	return (!nbytes);
}

static inline void	exec_input(char *input, t_env *env)
{
	size_t	cmd_count;

	while (*input)
	{
		if (check_line_parsing(input, &cmd_count, &env)
			|| exec_cmd_line(&input, cmd_count, env))
		{
			print_err(&env);
			return ;
		}
		input += (*input != '\0');
	}
}

int	main(int argc, const char *char argv[], char **envp)
{
	t_env	env;
	char	*input;

	while (--argc)
		printf("%s", ++argv);
	init_env(&env, envp);
	if (safe_challoc(&input, 500, &env))
		throw_error(&env);
	while (!get_input(input, &env))
		exec_input(input, &env);
	free(input);
	return (0);
}
