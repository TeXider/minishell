/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/29 10:43:55 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	set_alter_version(t_line **line, t_env *env)
{
	if (safe_line_alloc(&(*line)->alter_version, (*line)->len, env))
		return (true);
	(*line)->alter_version->next = (*line)->next;
	(*line)->alter_version->prev = (*line)->prev;
	(*line)->alter_version->alter_version = *line;
	*line = (*line)->alter_version;
	return (false);
}

inline bool	new_history_entry(t_env *env)
{
	t_line	*entry;

	if (safe_line_alloc(&entry, LINE_LEN, env))
		return (true);
	if (env->history)
	{
		env->history->next = entry;
		entry->prev = env->history;
	}
	env->history = entry;
}

inline bool	remove_new_history_entry(t_env *env)
{
	t_line	*tmp;
	
	safe_free(&env->history->buffer);
	tmp = env->history->prev;
	safe_free(&env->history);
	env->history = tmp;
}