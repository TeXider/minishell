/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/29 09:06:37 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (create_error(NULL, SYS_ERR, env));
	(*dst)[len] = '\0';
	return (false);
}

inline bool	safe_line_alloc(t_line **line, size_t len, t_env *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_challoc(&(*line)->buffer, len, env))
		return (create_error("malloc()", SYS_ERR, env));
	(*line)->len = len;
	(*line)->count = 0;
	(*line)->index = 0;
	(*line)->curr_char = '\0';
	(*line)->alter_version = NULL;
	return (false);
}

inline bool	set_correct_line_len(t_line *line, t_env *env)
{
	char	*tmp;
	size_t	i;

	if (line->count < line->len)
		return (false);
	if (safe_challoc(&tmp, line->len + LINE_SIZE, env))
		return (true);
	i = -1;
	while (++i < line->len)
		tmp[i] = line->buffer[i];
	line->len += LINE_SIZE;
	free(line->buffer);
	return (false);
}
