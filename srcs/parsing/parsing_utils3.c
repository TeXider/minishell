/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:40:22 by almighty          #+#    #+#             */
/*   Updated: 2025/12/19 11:41:42 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

inline bool	str_eq(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == *str2 || (*str1 == '\n' && !*str2)
		|| (!*str1 && *str2 == '\n'));
}

inline void	reset_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd)
{
	cmdp->saved_str = NULL;
	cmdp->sep = ' ';
	cmdp->in_expand = false;
	cmdp->argv_len = 0;
	cmdp->redirv_i = 0;
	cmdp->argv_i = 0;
	cmdp->cmd = cmd;
}

inline bool	get_raw_arg(char **dst, t_cmd_parsing *cmdp, bool put_in_quotes,
	t_env *env)
{
	char	*tmp_str;
	size_t	i;

	i = 0;
	tmp_str = cmdp->str;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		cmdp->str++;
		i++;
	}
	if (safe_challoc(dst, i + 2 * put_in_quotes, env))
		return (true);
	cmdp->str = tmp_str;
	if (put_in_quotes)
		(*dst)[0] = '`';
	i = put_in_quotes;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		(*dst)[i++] = *(cmdp->str++);
	}
	if (put_in_quotes)
		(*dst)[i] = '\'';
	return (false);
}

inline bool	is_control_op(char *str)
{
	return (*str == '|' || (*str == '&' && *(str + 1) == '&'));
}

inline bool	is_end_of_line(char *str)
{
	return (!*str || *str == '\n');
}