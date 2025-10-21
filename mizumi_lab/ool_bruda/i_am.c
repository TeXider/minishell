/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_am.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:53:41 by almighty          #+#    #+#             */
/*   Updated: 2025/09/23 09:22:30 by almighty         ###   ########.fr       */
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

bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

bool	is_end_of_cmd(char c, char sep)
{
	return (c == '\0' || (sep == ' ' && (c == '|' || c == '\n')));
}

bool	is_end_of_arg(char c, char sep)
{
	return (c == '\0' || (sep == ' ' && (c == ' ' || c == '>' || c == '<'
		|| is_end_of_cmd(c, sep))));
}

void	set_sep(char *sep, char c)
{
	*sep += (' ' - *sep) * (c == *sep)
			+ (c - *sep) * (*sep == ' ' && (c == '\'' || c == '"'));
}

bool	str_eq(char *str1, char *str2, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (str1[i] != str2[i])
			return (false);
	return (true);
}

int	get_var(char **name, t_var *res, t_env *env)
{
	size_t	len;
	size_t	i;

	(*name) += (**name == '$');
	len = 0;
	while ((*name)[len] && is_var_char((*name)[len]))
		len++;
	i = -1;
	while (++i < env->envp_len)
	{
		if (str_eq(*name, env->envp[i]->name, len))
		{
			*name += len - 1;
			res->name = env->envp[i]->name;
			res->val = env->envp[i]->val;
			return (0);
		}
	}
	*name += len - 1;
	res->name = NULL;
	res->val = NULL;
	return (1);
}

bool	check_var_empty(char **var_str, t_env *env)
{
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	i = -1;
	while (var.val[++i])
		if (var.val[i] != ' ')
			return (false);
	return (true);
}

bool	check_ambiguous_var(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
		&& var.val[i + 1] != ' ')
			return (true);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (false);
}

int	check_var_validity(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (1);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
		&& var.val[i + 1] != ' ')
			return (2);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (!has_arg);
}

int	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
	return (' ');
}

int	go_to_end_of_redir(char **redir, t_env *env)
{
	char	sep;
	bool	is_empty;
	bool	is_hdoc;
	int		var_status;

	is_empty = true;
	is_hdoc = (**redir == '<' && (*redir)[1] == '<');
	*redir += 1 + ((**redir == '>' && (*redir)[1] == '>') || is_hdoc);
	sep = skip_spaces(redir);
	while (!is_end_of_arg(**redir, sep))
	{
		if (!is_hdoc && sep != '\'' && **redir == '$'
			&& is_var_char(*(*redir + 1)))
		{
			var_status = check_var_validity(redir, env);
			if (sep != '"' && var_status == 2)
				return (4);
			is_empty &= (var_status == 1);
		}
		else
			is_empty &= (**redir == ' ');
		set_sep(&sep, **redir);
		(*redir)++;
	}
	return (2 * (sep != ' ') | is_empty);
}

int	go_to_end_of_arg(char **arg, t_env *env)
{
	char	sep;
	int		is_empty;

	sep = ' ';
	is_empty = 1;
	while (!is_end_of_arg(**arg, sep))
	{
		if (sep != '\'' && **arg == '$' && is_var_char(*(*arg + 1)))
			is_empty &= check_var_empty(arg, env);
		else
			is_empty &= (**arg == ' ');
		set_sep(&sep, **arg);
		(*arg)++;
	}
	return (2 * (sep != ' ') | is_empty);
}

int	get_cmd_lens(char *cmd, size_t *argv_len, size_t *redir_len, t_env *env)
{
	int	tmp;

	*redir_len = 0;
	*argv_len = 0;
	while (!is_end_of_cmd(*cmd, ' '))
	{
		if (*cmd == '>' || *cmd == '<')
		{
			tmp = go_to_end_of_redir(&cmd, env);
			if (tmp)
				return (1);
			(*redir_len)++;
		}
		else if (*cmd != ' ')
		{
			tmp = go_to_end_of_arg(&cmd, env);
			if (tmp == 2)
				return (1);
			(*argv_len) += !tmp;
		}
		else
			cmd++;
	}
	return (!*redir_len && !*argv_len);
}

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
