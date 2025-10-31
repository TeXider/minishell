/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/31 11:26:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (create_error("malloc()", SYS_ERR, env));
	(*dst)[len] = '\0';
	return (false);
}

inline void	safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
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
	return (false);
}

inline void	safe_free_line(t_line **line)
{
	if (*line)
	{
		safe_free((void **) &(*line)->buffer);
		free(*line);
		*line = NULL;
	}
}

inline bool	safe_history_alloc(t_hist **history, t_env *env)
{
	*history = malloc(sizeof(t_hist));
	if (!*history)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_line_alloc(&(*history)->edit_line, LINE_LEN, env))
	{
		free(*history);
		return (create_error("malloc()", SYS_ERR, env));
	}
	(*history)->edit_line->len = LINE_LEN;
	(*history)->edit_line->count = 0;
	(*history)->og_line = (*history)->edit_line;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (false);
}
