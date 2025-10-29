/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/29 10:42:54 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (create_error("malloc()", SYS_ERR, env));
	(*dst)[len] = '\0';
	return (false);
}

inline bool	safe_line_alloc(t_line **line, size_t len, t_env *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_challoc(&(*line)->buffer, len, env))
	{
		free(*line);
		return (create_error("malloc()", SYS_ERR, env));
	}
	(*line)->len = len;
	(*line)->count = 0;
	(*line)->index = 0;
	(*line)->curr_char = '\0';
	(*line)->alter_version = NULL;
	(*line)->next = NULL;
	(*line)->prev = NULL;
	return (false);
}

inline bool	set_correct_line_len(t_line *line, t_env *env)
{
	char	*tmp;
	size_t	i;

	if (line->count < line->len)
		return (false);
	if (safe_challoc(&tmp, line->len + LINE_LEN, env))
		return (true);
	i = -1;
	while (++i < line->len)
		tmp[i] = line->buffer[i];
	line->len += LINE_LEN;
	free(line->buffer);
	line->buffer = tmp;
	return (false);
}

inline char	*create_truncated_buff(t_line *line, t_env *env)
{
	char	*tmp;
	size_t	i;

	if (safe_challoc(&tmp, line->count, env))
		return (NULL);
	i = -1;
	while (++i < line->count)
		tmp[i] = line->buffer[i];
	return (tmp);
}
