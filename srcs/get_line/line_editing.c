/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:35:25 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:43:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline bool	set_correct_line_len(t_line *line, t_gl *env)
{
	char	*tmp;
	size_t	i;

	if (line->count < line->len)
		return (false);
	if (safe_challoc(&tmp, line->len + LINE_LEN, env))
		return (true);
	i = -1;
	while (++i < line->len)
		tmp[i] = line->buffer[i];
	line->len += LINE_LEN;
	free(line->buffer);
	line->buffer = tmp;
	return (false);
}

static inline void	move_rest_of_buff_to_right(t_line *line)
{
	size_t	i;

	i = line->count;
	while (--i >= line->index && i != (size_t)(-1))
		line->buffer[i + 1] = line->buffer[i];
}

static inline void	move_rest_of_buff_to_left(t_line *line)
{
	size_t	i;

	i = line->index;
	while (++i < line->count)
		line->buffer[i - 1] = line->buffer[i];
}

bool	delete_char(t_line **line, t_gl *env)
{
	if (set_edit_line(line, env))
		return (true);
	if ((((*line)->curr_char == RETURN || (*line)->curr_char == CTRL_RETURN)
			&& !(*line)->index)
		|| (((*line)->curr_char == DEL || (*line)->curr_char == CTRL_DEL)
			&& (*line)->index == (*line)->count))
		return (false);
	(*line)->index -= ((*line)->curr_char == RETURN
			|| (*line)->curr_char == CTRL_RETURN);
	move_rest_of_buff_to_left(*line);
	(*line)->count--;
	return (false);
}

bool	add_char(t_line **line, t_gl *env)
{
	if (set_edit_line(line, env))
		return (true);
	move_rest_of_buff_to_right(*line);
	(*line)->buffer[(*line)->index] = (*line)->curr_char;
	(*line)->index++;
	(*line)->count++;
	return (set_correct_line_len(*line, env));
}
