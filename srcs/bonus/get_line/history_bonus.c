/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:33 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line_bonus.h"

inline void	move_in_history(t_line **line, int term_cols, t_gl *env)
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

inline bool	overwrite_new_history_entry(t_line *line, t_gl *env)
{
	t_hist	*curr_hist;

	curr_hist = env->history;
	go_to_last_history_entry(env);
	safe_free_line(&env->history->edit_line);
	if (curr_hist->edit_line == curr_hist->og_line)
	{
		if (dup_line(curr_hist->edit_line, &line, env))
			return (true);
	}
	env->history->edit_line = line;
	env->history->og_line = line;
	curr_hist->edit_line = curr_hist->og_line;
	return (false);
}

inline bool	new_history_entry(t_gl *env)
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

inline void	remove_new_history_entry(t_gl *env)
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

inline bool	update_history(t_line *line, t_gl *env)
{
	if (env->update_history && env->history->next
		&& overwrite_new_history_entry(line, env))
		return (true);
	if (!env->update_history || !line->count)
		remove_new_history_entry(env);
	else
		env->line_count++;
	go_to_last_history_entry(env);
	return (false);
}
