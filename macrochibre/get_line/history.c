/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/14 08:57:43 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	move_in_history(t_line **line, int term_cols, t_env *env)
{
	if (((*line)->curr_char == ARROW_UP && !env->history->prev)
		|| ((*line)->curr_char == ARROW_DOWN && !env->history->next))
			return ;
	if ((*line)->curr_char == ARROW_UP)
		env->history = env->history->prev;
	else if ((*line)->curr_char == ARROW_DOWN)
		env->history = env->history->next;
	reset_line(*line);
	*line = env->history->edit_line;
	rewrite_line(*line, term_cols, env);
}

inline void	overwrite_new_history_entry(t_line *line, t_env *env)
{
	t_hist	*curr_hist;

	curr_hist = env->history;
	go_to_last_history_entry(env);
	safe_free_line(&env->history->edit_line);
	env->history->edit_line = line;
	env->history->og_line = line;
	curr_hist->edit_line = curr_hist->og_line;
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
	go_to_last_history_entry(env);
	safe_free_line(&env->history->edit_line);
	if (env->history->prev)
	{
		env->history = env->history->prev;
		safe_free((void **) &env->history->next);
	}
	else
		safe_free((void **)&env->history);
}

inline void	update_history(t_line *line, t_env *env)
{
	if (env->update_history && env->history->next)
		overwrite_new_history_entry(line, env);
	if (!env->update_history || !line->count)
		remove_new_history_entry(env);
	if (env->history)
		go_to_last_history_entry(env);
}
