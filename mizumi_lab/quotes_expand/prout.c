/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:46:11 by almighty          #+#    #+#             */
/*   Updated: 2025/09/10 12:43:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_cmd
{
	char	**envp;
	char	*path;
}	t_cmd;

typedef struct s_env
{
	t_var	**envp;
	size_t	envp_len;
	t_cmd	**cmd_list;
	char	**path_list;
	char	*empty_string;
}	t_env;

int	set_challoc(char **ptr, ssize_t size, t_env *env)
{
	(void) env;
	if (size == -1)
		return (1);
	*ptr = malloc(size * sizeof(char) + 1);
	if (!*ptr)
		return (1);
	(*ptr)[size] = '\0';
	return (0);
}

int	is_token(char *str)
{
	return (*str == '|' || *str == '>' || *str == '<' || *str == '('
		|| *str == ')' || *str == '\n' || (*str == '&' && *(str + 1) == '&'));
}

ssize_t	quotes_expand_len(char *arg, t_env *env)
{
	char	sep;
	ssize_t	len;

	(void) env;
	sep = ' ';
	len = 0;
	while (*arg && !(sep == ' ' && (*arg == ' ' || is_token(arg))))
	{
		if ((sep != ' ' && *arg == sep) || (sep == ' '
				&& (*arg == '\'' || *arg == '"')))
			sep += (*arg - sep) * (sep == ' ' && (*arg == '\'' || *arg == '"'))
				+ (' ' - sep) * (*arg == sep);
		else
			len++;
		arg++;
	}
	if (sep != ' ')
		return (-1);
	printf("Calc len : %zu\n", len);
	return (len);
}

int	quotes_expand(char *arg, char **res, t_env *env)
{
	char	sep;
	size_t	i;

	if (set_challoc(res, quotes_expand_len(arg, env), env))
		return (1);
	sep = ' ';
	i = 0;
	while (*arg && !(sep == ' ' && (*arg == ' ' || is_token(arg))))
	{
		if ((sep != ' ' && *arg == sep) || (sep == ' '
				&& (*arg == '\'' || *arg == '"')))
			sep += (*arg - sep) * (sep == ' ' && (*arg == '\'' || *arg == '"'))
				+ (' ' - sep) * (*arg == sep);
		else
			(*res)[i++] = *arg;
		arg++;
	}
	return (0);
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