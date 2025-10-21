/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:26:39 by almighty          #+#    #+#             */
/*   Updated: 2025/09/23 09:37:21 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
	return (' ');
}
