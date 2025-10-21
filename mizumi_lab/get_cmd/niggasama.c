/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niggasama.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:20:47 by almighty          #+#    #+#             */
/*   Updated: 2025/09/15 10:52:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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

int	set_lalloc(char ***dst, size_t size, t_env *env)
{
	*dst = malloc(sizeof(char *) * (size + 1));
	if (!*dst)
		return (1);
	(*dst)[size] = NULL;
	return (0);
}

int	go_to_end_of_arg(char **arg, t_env *env)
{
	char	sep;

	sep = ' ' + (**arg - ' ') * (**arg == '\'' || **arg == '"');
	*arg += (sep != ' ');
	while (**arg && !(sep == ' ' && is_token(**arg)))
	{
		sep += (' ' - sep) * (**arg == sep)
			+ (**arg - sep) * (sep == ' ' && (**arg == '\'' || **arg == '"'));
		(*arg)++;
	}
	return (sep != ' ');
}

int	get_cmd_len(char *cmd, size_t *argv_len, size_t *files_len, t_env *env)
{
	while (*cmd)
	{
		if (*cmd == '>' || *cmd == '<')
		{
			cmd += 1 + ((*cmd == '>' && cmd[1] == '>')
					|| (*cmd == '>' && cmd[1] == '>'));
			if (go_to_end_of_arg(&cmd, env))
				return (1);
			(*files_len)++;
		}
		else if (*cmd != ' ')
		{
			if (go_to_end_of_arg(&cmd, env))
				return (1);
			(*argv_len)++;
		}
		else
			cmd++;
	}
}

int	get_cmd(char *cmd, t_cmd *res, t_env *env)
{
	size_t	argv_len;
	size_t	files_len;

	argv_len = 0;
	files_len = 0;
	if (get_cmd_len(cmd, &argv_len, &files_len, env)
		|| set_lalloc(&(res->argv), argv_len, env)
		|| set_lalloc(&(res->redir), files_len, env)
		|| get_args(res, env))
		return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	t_env	env;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(t_var *) * 3);
	env.envp_len = 3;
	env.envp[0] = malloc(sizeof(t_var)); env.envp[1] = malloc(sizeof(t_var)); env.envp[2] = malloc(sizeof(t_var));
	env.envp[0]->name = "caca"; env.envp[1]->name = "fesse"; env.envp[2]->name = "prout";
	env.envp[0]->val = "general"; env.envp[1]->val = "balletrou"; env.envp[2]->val = "frakaka";
	char	*input = malloc(500 * sizeof(char));
	input[read(0, input, 499)] = '\0';
	char	*res;
	if (quotes_expand(input, &res, &env))
		return (printf("mr poopybutthole\n"));
	int i;
	for (i = 0; res[i]; i++)
		write(1, res + i, 1);
	write(1, "\n", 1);
	printf("Conc len : %d\n", i);
	free(res);
	free(input);
	free(env.envp[0]); free(env.envp[1]); free(env.envp[2]);
	free(env.envp);
}