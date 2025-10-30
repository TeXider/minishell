/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:09:57 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 13:53:48 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	set_line_on_history(t_line *line, t_env *env)
{
	if (env->history->edit_buffer)
		line->buffer = env->history->edit_buffer;
	else
		line->buffer = env->history->buffer;
	line->count = env->history->count;
	line->len = env->history->len;
	line->index = line->count;
	line->curr_char = '\0';
}

inline void	update_history(t_line *line, t_env *env)
{
	if (env->history->edit_buffer)
		env->history->edit_buffer = line->buffer;
	else
		env->history->buffer = line->buffer;
	env->history->count = line->count;
	env->history->len = line->len;
}

inline bool	set_edit_line(t_line *line, t_env *env)
{
	if (env->history->next && !env->history->og_line)
	{
		if (safe_line_alloc(&env->history->edit_line,
			env->history->og_line->len, env))
			return (true);
		cpy_str(env->history->buffer, env->history->edit_buffer, env->history->len);
		line->buffer = env->history->edit_buffer;
	}
	return (false);
}
