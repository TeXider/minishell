/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_lens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:33:57 by almighty          #+#    #+#             */
/*   Updated: 2025/09/23 09:55:56 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (2 * (!*redir_len && !*argv_len));
}
