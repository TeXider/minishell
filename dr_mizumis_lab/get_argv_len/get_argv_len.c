/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/10/09 09:50:21 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	go_to_end_of_redir(char **redir, t_env *env)
{
	(void)	env;
	bool	is_empty;
	char	sep;
	
	*redir += 1 + ((**redir == '>' && **(redir + 1) == '>')
			|| (**redir == '<' && **(redir + 1) == '<'));
	skip_spaces(redir);
	is_empty = true;
	sep = ' ';
	while (!is_end_of_arg(**redir, sep))
	{
		is_empty = false;
		set_sep(&sep, **redir);
		(*redir)++;
	}
	return (is_empty | (sep != ' '));
}

static inline void	count_args_in_var(char **arg, size_t *argv_len,
		bool *has_start, t_env *env)
{
	t_var	var;
	size_t	i;
	
	if (get_var(arg, &var, env))
		return ;
	i = -1;
	while (var.val[++i])
	{
		*argv_len += (!*has_start && var.val[i] != ' ');
		*has_start = (var.val[i] != ' ');
	}
}

bool	count_arg(char **arg, size_t *argv_len, t_env *env)
{
	char	sep;
	bool	has_start;

	has_start = false;
	sep = ' ';
	while (!is_end_of_arg(**arg, sep))
	{
		if (sep == ' ' && **arg == '$' && is_var_char(*(*arg + 1)))
			count_args_in_var(arg, argv_len, &has_start, env);
		else
		{
			*argv_len += !has_start;
			has_start = true;
		}
		set_sep(&sep, **arg);
		(*arg)++;
	}
	if (sep != ' ')
		return (true);
	return (false);
}

bool	get_argv_len(char *cmd, size_t *argv_len, t_env *env)
{
	*argv_len = 0;
	while (!is_end_of_cmd(*cmd, ' '))
	{
		if (*cmd == '>' || *cmd == '<')
		{
			if (go_to_end_of_redir(&cmd, env))
				return (true);
		}
		else if (*cmd != ' ')
		{
			if (count_arg(&cmd, argv_len, env))
				return (true);
		}
		else
			cmd++;
	}
	return (false);
}
