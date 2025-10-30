/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:09:57 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 12:47:56 by almighty         ###   ########.fr       */
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

inline bool	set_edit_buffer(t_line *line, t_env *env)
{
	if (env->history->next && !env->history->edit_buffer)
	{
		if (safe_challoc(&env->history->edit_buffer, env->history->len, env))
			return (true);
		cpy_str(env->history->buffer, env->history->edit_buffer, env->history->len);
		line->buffer = env->history->edit_buffer;
	}
	return (false);
}
