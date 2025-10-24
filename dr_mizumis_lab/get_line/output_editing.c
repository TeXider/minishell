/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_editing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:58:05 by almighty          #+#    #+#             */
/*   Updated: 2025/10/24 12:46:50 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline int	get_curr_col(t_line *line, int term_cols, t_env *env)
{
	return ((line->index + env->prompt_len - 1) % term_cols);
}

inline bool	get_term_cols(int *term_cols, t_env *env)
{
	struct winsize	win;

	if (ioctl(STD_IN, TIOCGWINSZ, &win))
		return (create_error("ioctl()", SYS_ERR, env));
	*term_cols = win.ws_col;
	return (false);
}

inline void	move_cursor(ssize_t distance, t_line *line, int term_cols,
	t_env *env)
{
	int		col;
	size_t	i;

	col = get_curr_col(line, term_cols, env);
	while (distance)
	{
		if ((distance < 0 && col == 0)
			|| (distance > 0 && col + 1 == term_cols))
		{
			write(1, "\x1b[A\x1b[B" + 3 * (distance > 0), 3);
			i = -1;
			while (++i < (size_t) term_cols)
				write(1, "\x1b[C\x1b[D" + 3 * (distance > 0), 3);
		}
		else
			write(1, "\x1b[C\x1b[D" + 3 * (distance < 0), 3);
		col += 1 - 2 * (distance < 0);
		col += term_cols * (col < 0);
		col %= term_cols;
		distance += 1 - 2 * (distance > 0);
	}
}

inline void	reset_line_output(t_line *line, int term_cols, t_env *env)
{
	size_t	i;
	
	if (line->count == 0)
		return ;
	move_cursor(line->count - line->index, line, term_cols, env);
	i = -1;
	while (++i < line->count)
	{
		write(1, "\b \b", 3);
		move_cursor(-1, line, term_cols, env);
	}
}

//assume cursor just after prompt
inline void	show_line_output(t_line *line, int term_cols, t_env *env)
{
	size_t	i;

	i = -1;
	while (++i < line->count)
		write(1, line->buffer + i, 1);
	move_cursor(0, line, term_cols, env);
	line->index = line->count;
}
