/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caca.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:07:10 by almighty          #+#    #+#             */
/*   Updated: 2025/09/15 11:19:27 by almighty         ###   ########.fr       */
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

size_t	cpy_str(char *src, char *dst)
{
	size_t	len;

	len = 0;
	while (src[len])
	{
		dst[len] = src[len];
		len++;
	}
	return (len);
}

int	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

int	str_eq(char *str1, char *str2, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len && str1[i] && str2[i])
		if (str1[i] != str2[i])
			return (0);
	return (i == len);
}

size_t	str_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

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

int	get_var(char **name, t_var *res, t_env *env)
{
	size_t	len;
	size_t	i;

	len = 0;
	while ((*name)[len] && is_var_char((*name)[len]))
		len++;
	i = -1;
	while (++i < env->envp_len)
	{
		if (str_eq(*name, env->envp[i]->name, len))
		{
			*name += len;
			res->name = env->envp[i]->name;
			res->val = env->envp[i]->val;
			return (0);
		}
	}
	*name += len;
	res->name = NULL;
	res->val = NULL;
	return (1);
}

size_t	expand_len(char *cmd, t_env *env)
{
	size_t	len;
	char	sep;
	t_var	var;

	len = 0;
	sep = ' ';
	while (*cmd)
	{
		if (sep != '\'' && *cmd == '$' && is_var_char(*(cmd + 1)))
		{
			cmd++;
			get_var(&cmd, &var, env);
			len += str_len(var.val);
		}
		else
		{
			sep += (*cmd - sep) * (sep == ' ' && (*cmd == '\'' || *cmd == '"'))
				+ (' ' - sep) * (*cmd == sep);
			len++;
			cmd++;
		}
	}
	printf("Calc len : %zu\n", len);
	return (len);
}

int	expand(char *cmd, char **dst, t_env *env)
{
	size_t	i;
	char	sep;
	t_var	var;

	if (set_challoc(dst, expand_len(cmd, env), env))
		return (1);
	i = 0;
	sep = ' ';
	while (*cmd)
	{
		if (sep != '\'' && *cmd == '$' && is_var_char(*(cmd + 1)))
		{
			cmd++;
			get_var(&cmd, &var, env);
			i += cpy_str(var.val, *dst + i);
		}
		else
		{
			sep += (*cmd - sep) * (sep == ' ' && (*cmd == '\'' || *cmd == '"'))
				+ (' ' - sep) * (*cmd == sep);
			(*dst)[i++] = *(cmd++);
		}
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
	expand(input, &res, &env);
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