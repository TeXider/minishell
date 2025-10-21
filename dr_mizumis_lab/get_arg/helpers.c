/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:26:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 08:15:46 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool	is_end_of_cmd(char c, char sep)
{
	return (c == '\0' || (sep == ' ' && (c == '|' || c == '\n')));
}

inline bool	is_end_of_arg(char c, char sep)
{
	return (c == '\0' || (sep == ' ' && (c == ' ' || c == '>' || c == '<'
				|| is_end_of_cmd(c, sep))));
}

inline void	set_sep(char *sep, char c)
{
	*sep += (' ' - *sep) * (c == *sep)
		+ (c - *sep) * (*sep == ' ' && (c == '\'' || c == '"'));
}

inline char	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
	return (' ');
}

inline bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
