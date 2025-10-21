/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_am.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/09/23 09:33:44 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**redir;
	char	*mode;
}	t_cmd;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_env
{
	t_var	**envp;
	size_t	envp_len;
	t_cmd	**cmd_list;
	char	**path_list;
	char	*empty_string;
}	t_env;

// int	get_cmd(char *cmd, t_cmd *res, t_env *env)
// {
// 	size_t	argv_len;
// 	size_t	redir_len;

// 	if (get_cmd_lens(cmd, &argv_len, &redir_len, env)
// 		|| set_lalloc(&(res->argv), argv_len, env)
// 		|| set_lalloc(&(res->redir), redir_len, env)
// 		|| set_malloc(&(res->mode), sizeof(char) * redir_len, env))
// 		return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	t_env	env;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(t_var *) * 3);
	env.envp_len = 3;
	env.envp[0] = malloc(sizeof(t_var)); env.envp[1] = malloc(sizeof(t_var)); env.envp[2] = malloc(sizeof(t_var));
	env.envp[0]->name = "caca"; env.envp[1]->name = "fesse"; env.envp[2]->name = "prout";
	env.envp[0]->val = ""; env.envp[1]->val = "balletrou"; env.envp[2]->val = "frakaka";
	char	*input = malloc(500 * sizeof(char));
	input[read(0, input, 499)] = '\0';
	size_t args_len = 0, redir_len = 0;
	get_cmd_lens(input, &args_len, &redir_len, &env);
	printf("argv : %zu, redir : %zu\n", args_len, redir_len);
	free(input);
	free(env.envp[0]); free(env.envp[1]); free(env.envp[2]);
	free(env.envp);
}
