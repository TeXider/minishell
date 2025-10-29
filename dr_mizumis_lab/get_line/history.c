/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/29 14:41:50 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	set_edit_buffer(t_line *line, t_env *env)
{
	if (safe_challoc(&env->history->edit_buffer, env->history->len, env))
		return (true);
	cpy_str(env->history->buffer, env->history->edit_buffer, env->history->len);
	set_line_on_history(line, env);
	return (false);
}

inline void	move_in_history(t_line *line, int term_cols, t_env *env)
{
	if ((line->curr_char == ARROW_UP && !env->history->prev)
		|| (line->curr_char == ARROW_DOWN && !env->history->next))
			return ;
	reset_line_output(line, term_cols, env);
	if (line->curr_char == ARROW_UP)
		env->history = env->history->prev;
	else if (line->curr_char == ARROW_DOWN)
		env->history = env->history->next;
	set_line_on_history(line, env);
	show_line_output(line, term_cols, env);
}

inline bool	overwrite_new_history_entry(t_line *line, t_env *env)
{
	while (env->history->next)
		env->history = env->history->next;
	safe_free(&env->history->buffer);
	safe_free(&env->history->edit_buffer);
	env->history->buffer = line->buffer;
}

inline bool	new_history_entry(t_env *env)
{
	if (!env->history)
	{
		if (safe_history_alloc(&env->history, env))
			return (true);
	}
	else
	{
		if (safe_history_alloc(&env->history->next, env))
			return (true);
		env->history->next->prev = env->history;
		env->history = env->history->next;
	}
	return (false);
}

inline void	remove_new_history_entry(t_env *env)
{
	t_hist	*tmp;

	safe_free((void **) &env->history->buffer);
	tmp = env->history->prev;
	safe_free((void **) &env->history);
	env->history = tmp;
}