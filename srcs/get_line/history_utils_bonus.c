/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:09:57 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:36 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line_bonus.h"

inline void	go_to_last_history_entry(t_gl *env)
{
	if (!env->history)
		return ;
	while (env->history->next)
		env->history = env->history->next;
}

inline bool	set_edit_line(t_line **line, t_gl *env)
{
	if (env->history->next && env->history->og_line == env->history->edit_line)
	{
		if (safe_line_alloc(&env->history->edit_line,
				env->history->og_line->len, env))
			return (true);
		cpy_str(env->history->og_line->buffer, env->history->edit_line->buffer,
			env->history->og_line->len);
		env->history->edit_line->len = env->history->og_line->len;
		env->history->edit_line->count = env->history->og_line->count;
		env->history->edit_line->index = env->history->og_line->index;
		env->history->edit_line->curr_char = env->history->og_line->curr_char;
		*line = env->history->edit_line;
	}
	return (false);
}

inline void	reset_line(t_line *line)
{
	line->curr_char = '\0';
	line->index = line->count;
}
