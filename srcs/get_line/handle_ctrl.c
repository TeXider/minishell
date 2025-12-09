/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:21:04 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/12/09 12:48:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline void	ctrl_move_cursor_right(size_t jump_len, t_line *line,
	int term_cols, t_gl *env)
{
	move_cursor(jump_len * (line->index < line->count), line->index, term_cols,
		env);
	line->index += jump_len * (line->index < line->count);
}

static inline void	ctrl_move_cursor_left(size_t jump_len, t_line *line,
	int term_cols, t_gl *env)
{
	move_cursor(-jump_len * (line->index > 0), line->index, term_cols,
		env);
	line->index -= jump_len * (line->index > 0);
}

static inline size_t	get_jump_len(t_line *line)
{
	int		dir;
	size_t	len;
	size_t	i;

	dir = LEFT * (line->curr_char == ARROW_LEFT
			|| line->curr_char == CTRL_RETURN)
		+ RIGHT * (line->curr_char == ARROW_RIGHT
			|| line->curr_char == CTRL_DEL);
	len = 1;
	i = line->index + dir;
	while (i > 0 && i < line->count
		&& !(dir == LEFT && line->buffer[i] != ' '
			&& line->buffer[i - 1] == ' ')
		&& !(dir == RIGHT && line->buffer[i] == ' '
			&& line->buffer[i - 1] != ' '))
	{
		len++;
		i += dir;
	}
	return (len);
}

bool	handle_ctrl(t_line **line, int term_cols, t_gl *env)
{
	size_t	i;
	size_t	jump_len;

	env->is_ctrl = false;
	if (!(*line)->count || !(*line)->curr_char)
		return (false);
	jump_len = get_jump_len(*line);
	if ((*line)->curr_char == ARROW_RIGHT)
		ctrl_move_cursor_right(jump_len, *line, term_cols, env);
	else if ((*line)->curr_char == ARROW_LEFT)
		ctrl_move_cursor_left(jump_len, *line, term_cols, env);
	else if ((*line)->curr_char == CTRL_DEL
		|| (*line)->curr_char == CTRL_RETURN)
	{
		i = -1;
		while (++i < jump_len)
			if (delete_char(line, env))
				return (true);
	}
	if ((*line)->curr_char == CTRL_DEL || (*line)->curr_char == CTRL_RETURN)
		rewrite_line(*line, term_cols, env);
	return (false);
}
