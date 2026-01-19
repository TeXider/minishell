/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:58:05 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 12:44:19 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

void	rewrite_line(t_line *line, int term_cols, t_gl *env)
{
	move_cursor(-env->prev_line_index, env->prev_line_index, term_cols, env);
	write(1, "\e[J", 3);
	write(1, line->buffer, line->count);
	write(1, "\n", curr_col(line->count, term_cols, env) == 0);
	move_cursor(line->index - line->count, line->count, term_cols, env);
}

// inline void	rewrite_line(t_line *line, int term_cols, t_gl *env)
// {
// 	size_t	max;
// 	size_t	i;

// 	move_cursor(-env->prev_line_index, env->prev_line_index, term_cols, env);
// 	max = env->prev_line_count + (line->count - env->prev_line_count)
// 		* (line->count > env->prev_line_count);
// 	i = -1;
// 	while (++i < max)
// 	{
// 		if (i < line->count)
// 			write(1, line->buffer + i, 1);
// 		else
// 			write(1, " ", 1);
// 	}
// 	write(1, "\n", get_curr_col(max, term_cols, env) == 0);
// 	if (env->prev_line_count > line->count)
// 		move_cursor(line->count - env->prev_line_count,
// 			env->prev_line_count, term_cols, env);
// 	move_cursor(line->index - line->count, line->count, term_cols, env);
// }
//CONDITIONAL INDICATION SIZE_T
