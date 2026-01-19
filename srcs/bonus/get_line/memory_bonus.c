/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:40 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line_bonus.h"

inline bool	safe_line_alloc(t_line **line, size_t len, t_gl *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
	{
		create_error("malloc()", FATAL_SYS_ERR, env->main_env);
		return (true);
	}
	if (safe_challoc(&(*line)->buffer, len, env->main_env))
	{
		free(*line);
		create_error("malloc()", FATAL_SYS_ERR, env->main_env);
		return (true);
	}
	(*line)->len = len;
	(*line)->count = 0;
	(*line)->index = 0;
	(*line)->curr_char = '\0';
	return (false);
}

inline bool	dup_line(t_line *src, t_line **dst, t_gl *env)
{
	size_t	i;

	if (safe_line_alloc(dst, src->len, env))
		return (true);
	(*dst)->count = src->count;
	(*dst)->index = src->index;
	(*dst)->curr_char = src->curr_char;
	i = -1;
	while (++i < src->count)
		(*dst)->buffer[i] = src->buffer[i];
	return (false);
}

inline void	safe_free_line(t_line **line)
{
	if (*line)
	{
		if ((*line)->buffer)
			free((*line)->buffer);
		safe_free((void **)line);
	}
}

inline bool	safe_history_alloc(t_hist **history, t_gl *env)
{
	*history = malloc(sizeof(t_hist));
	if (!*history)
	{
		create_error("malloc()", FATAL_SYS_ERR, env->main_env);
		return (true);
	}
	if (safe_line_alloc(&(*history)->og_line, LINE_LEN, env))
	{
		free(*history);
		*history = NULL;
		create_error("malloc()", FATAL_SYS_ERR, env->main_env);
		return (true);
	}
	(*history)->og_line->len = LINE_LEN;
	(*history)->og_line->count = 0;
	(*history)->edit_line = (*history)->og_line;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (false);
}

inline void	safe_free_history(t_gl *env)
{
	t_hist	*tmp;

	go_to_last_history_entry(env);
	while (env->history)
	{
		if (env->history->edit_line != env->history->og_line)
			safe_free_line(&env->history->edit_line);
		safe_free_line(&env->history->og_line);
		tmp = env->history->prev;
		free(env->history);
		env->history = tmp;
	}
}
