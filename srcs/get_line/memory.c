/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 09:50:58 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

inline bool	safe_line_alloc(t_line **line, size_t len, t_gl *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
	{
		create_error("malloc()", SYS_ERR, env->main_env);
		return (true);
	}
	if (safe_challoc(&(*line)->buffer, len, env))
	{
		free(*line);
		create_error("malloc()", SYS_ERR, env->main_env);
		return (true);
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
		if ((*line)->buffer)
			free((*line)->buffer);
		safe_free((void **) line);
	}
}

inline bool	safe_history_alloc(t_hist **history, t_gl *env)
{
	*history = malloc(sizeof(t_hist));
	if (!*history)
	{
		create_error("malloc()", SYS_ERR, env->main_env);
		return (true);
	}
	if (safe_line_alloc(&(*history)->edit_line, LINE_LEN, env))
	{
		free(*history);
		create_error("malloc()", SYS_ERR, env->main_env);
		return (true);
	}
	(*history)->edit_line->len = LINE_LEN;
	(*history)->edit_line->count = 0;
	(*history)->og_line = (*history)->edit_line;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (false);
}
