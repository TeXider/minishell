/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_editing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:58:05 by almighty          #+#    #+#             */
/*   Updated: 2025/11/22 14:06:56 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	move_cursor(ssize_t distance, size_t index, int term_cols,
	t_env *env)
{
	int		col;
	size_t	i;

	col = get_curr_col(index, term_cols, env);
	while (distance)
	{
		if ((distance < 0 && col == 0)
			|| (distance > 0 && col + 1 == term_cols))
		{
			write(1, "\033[A\033[B" + 3 * (distance > 0), 3);
			i = -1;
			while (++i < (size_t) term_cols)
				write(1, "\033[C\033[D" + 3 * (distance > 0), 3);
		}
		else
			write(1, "\033[C\033[D" + 3 * (distance < 0), 3);
		col += 1 - 2 * (distance < 0);
		col += term_cols * (col < 0);
		col %= term_cols;
		distance += 1 - 2 * (distance > 0);
	}
}

inline void	reset_line_output(t_line *line, int term_cols, t_env *env)
{
	size_t	index;
	size_t	i;

	if (line->count == 0)
		return ;
	move_cursor(line->count - line->index, line->index, term_cols, env);
	i = -1;
	index = line->count;
	while (++i < line->count)
	{
		move_cursor(-1, index, term_cols, env);
		write(1, " ", 1);
		move_cursor(-(get_curr_col(index, term_cols, env) != 0),
			index, term_cols, env);
		index--;
	}
}

inline void	show_line_output(t_line *line, int term_cols, t_env *env)
{
	size_t	i;

	if (!line->count)
		return ;
	i = -1;
	while (++i < line->count)
		write(1, line->buffer + i, 1);
	write(1, "\n", get_curr_col(line->count, term_cols, env) == 0);
	move_cursor(line->index - line->count, line->count, term_cols, env);
}

inline void	rewrite_line(t_line *line, int term_cols, t_env *env)
{
	size_t	max;
	size_t	i;

	move_cursor(-env->prev_line_index, env->prev_line_index, term_cols, env);
	max = env->prev_line_count + (line->count - env->prev_line_count)
		* (line->count > env->prev_line_count);
	i = -1;
	while (++i < max)
	{
		if (i < line->count)
			write(1, line->buffer + i, 1);
		else
			write(1, " ", 1);
	}
	write(1, "\n", get_curr_col(max, term_cols, env) == 0);
	if (env->prev_line_count > line->count)
		move_cursor(line->count - env->prev_line_count,
			env->prev_line_count, term_cols, env);
	move_cursor(line->index - line->count, line->count, term_cols, env);
}
//CONDITIONAL INDICATION SIZE_T
