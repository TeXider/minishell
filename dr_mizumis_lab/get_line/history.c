/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 12:47:01 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

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

inline void	overwrite_new_history_entry(t_line *line, t_env *env)
{
	while (env->history->next)
		env->history = env->history->next;
	safe_free((void **) &env->history->buffer);
	env->history->buffer = line->buffer;
	env->history->len = line->len;
	env->history->count = line->count;
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