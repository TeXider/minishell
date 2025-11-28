/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:26:39 by almighty          #+#    #+#             */
/*   Updated: 2025/11/14 13:16:37 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline bool	is_end_of_cmd(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && (*(cmdp->str) == '\0' || (cmdp->sep == ' '
				&& (*(cmdp->str) == '|' || *(cmdp->str) == '\n'))));
}

inline bool	is_end_of_arg(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '\0' || (cmdp->sep == ' '
			&& (*(cmdp->str) == ' ' || *(cmdp->str) == '>'
				|| *(cmdp->str) == '<' || is_end_of_cmd(cmdp))));
}

inline void	set_sep(t_cmd_parsing *cmdp)
{
	cmdp->sep += (!cmdp->in_expand)
		* ((' ' - cmdp->sep) * (*(cmdp->str) == cmdp->sep)
			+ (*(cmdp->str) - cmdp->sep)
			* (cmdp->sep == ' ' && (*(cmdp->str) == '\''
					|| *(cmdp->str) == '"')));
}

inline void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

inline bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
