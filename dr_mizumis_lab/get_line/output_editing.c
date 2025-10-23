/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_editing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:58:05 by almighty          #+#    #+#             */
/*   Updated: 2025/10/23 12:28:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	get_win_size(t_env *env)
{
	struct winsize	win;

	if (ioctl(STD_IN, TIOCGWINSZ, &win))
		return (create_error("ioctl()", SYS_ERR, env));
	env->win_cols = win.ws_col;
	env->win_rows = win.ws_row;
	return (false);
}

inline bool	move_cursor(ssize_t distance, size_t curr_col, t_env *env)
{
	while (distance)
	{
		write(1, "\x1b[A\x1b[C\x1b[C\x1b[C",
			12 * (distance < 0 && curr_col == 0));
		write(1, "\x1b[B\x1b[D\x1b[D\x1b[D",
			12 * (distance > 0 && curr_col + 1 == env->win_cols));
		write(1, "\x1b[C\x1b[D" + 3 * (distance < 0), 3 * (curr_col != 0 &&
			curr_col + 1 == env->win_cols));
		distance += 1 - 2 * (distance > 0);
	}
}

//assume index just after prompt
inline bool	show_line_ouput(t_line *line, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < line->count)
		write(1, line->buffer[i++], 1);
	return (move_cursor(line->count,
		(line->index + (env->prompt_len
		* ((env->prompt_len + line->index) / env->win_cols == 0))
		% env->win_cols), env));
}
