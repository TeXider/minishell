/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:21:04 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/28 13:43:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

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
	i = -1;
	while (++i < jump_len)
	{
		if ((*line)->curr_char == ARROW_LEFT
			|| (*line)->curr_char == ARROW_RIGHT)
			handle_lr_arrows(*line, term_cols, env);
		else if ((*line)->curr_char == CTRL_DEL
			|| (*line)->curr_char == CTRL_RETURN)
		{
			if (delete_char(line, env))
				return (true);
		}
	}
	if ((*line)->curr_char == CTRL_DEL || (*line)->curr_char == CTRL_RETURN)
		rewrite_line(*line, term_cols, env);
	return (false);
}
