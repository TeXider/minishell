/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:26:39 by almighty          #+#    #+#             */
/*   Updated: 2026/01/14 13:05:50 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline bool	is_end_of_shell(char *line, bool is_subshell)
{
	return (!*line || *line == '\n' || (is_subshell && *line == ')'));
}

inline bool	is_end_of_cmd(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && (*(cmdp->str) == '\0' || (cmdp->sep == ' '
				&& (is_control_op(cmdp->str) || *(cmdp->str) == '('
					|| *(cmdp->str) == ')' || *(cmdp->str) == '\n'))));
}

inline bool	is_end_of_arg(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '\0' || *(cmdp->str) == '\n' || (cmdp->sep == ' '
			&& (*(cmdp->str) == ' ' || (!cmdp->in_expand
					&& (*(cmdp->str) == '>'
						|| *(cmdp->str) == '<' || is_end_of_cmd(cmdp))))));
}

inline void	set_sep(t_cmd_parsing *cmdp)
{
	cmdp->sep += (!cmdp->in_expand)
		* ((' ' - cmdp->sep) * (*(cmdp->str) == cmdp->sep)
			+ (*(cmdp->str) - cmdp->sep)
			* (cmdp->sep == ' ' && (*(cmdp->str) == '\''
					|| *(cmdp->str) == '"')));
}

inline bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
