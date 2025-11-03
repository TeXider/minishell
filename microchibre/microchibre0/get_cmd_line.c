/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:50:16 by almighty          #+#    #+#             */
/*   Updated: 2025/11/03 10:33:31 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	get_cmd(char **cmd_str, t_cmd *res, t_env *env)
{
	size_t	argv_len;
	size_t	arg_i;

	if (get_argv_len(*cmd_str, res, &argv_len, env)
		|| safe_lalloc(&(res->argv), argv_len, env))
		return (false);
	arg_i = 0;
	while (!is_end_of_cmd(**cmd_str, ' '))
	{
		if (!res->start_ptr && cmd_str != ' ')
			res->start_ptr = cmd_str;
		if (**cmd_str == '>' || **cmd_str == '<')
		{
			if (get_redir(cmd_str, res, env))
				return (true);
		}
		else if (**cmd_str != ' ')
		{
			if (get_arg(cmd_str, res, &arg_i, env))
				return (true);
		}
		else
			(*cmd_str)++;
	}
	return (false);
}

static inline bool	init_check_line_parsing(size_t *cmd_list_len,
	bool *has_pipe, bool *is_empty)
{
	*cmd_list_len = 0;
	*has_pipe = false;
	*is_empty = true;
}

static inline bool	check_line_parsing(char *line, size_t *cmd_list_len,
	t_env *env)
{
	bool	has_pipe;
	bool	is_empty;

	init_check_line_parsing(cmd_list_len, &has_pipe, &is_empty);
	while (*line && *line != '\n')
	{
		if (go_to_end_of_cmd(&line, &is_empty, cmd_list_len,
				env))
			return (true);
		if (is_empty && (*line == '|' || has_pipe))
		{
			create_error(line, UNEXPECTED_TOKEN_ERR, env);
			return (true);
		}
		is_empty = true;
		has_pipe = (*line == '|');
		line += (has_pipe);
	}
	if (has_pipe && is_empty)
	{
		create_error(line, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (false);
}

bool	get_cmd_line(char **line, t_cmd **cmd_list, t_env *env)
{
	size_t	cmd_list_len;
	size_t	i;

	if (check_line_parsing(*line, &cmd_list_len, env))
		return (true);
	if (!cmd_list_len)
		return (false);
	if (safe_cmdlalloc(cmd_list, cmd_list_len, env))
		return (true);
	i = 0;
	while (**line && **line != '\n')
	{
		set_new_cmd(*cmd_list + i, env);
		if (get_cmd(line, *cmd_list + i, env))
			return (true);
		(*line) += (**line == '|');
		i++;
	}
	return (false);
}
