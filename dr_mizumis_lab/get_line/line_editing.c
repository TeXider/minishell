/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:35:25 by almighty          #+#    #+#             */
/*   Updated: 2025/10/30 12:29:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	move_rest_of_buff_to_right(t_line *line)
{
	size_t	i;

	i = line->count;
	while (--i >= line->index && i != (size_t)(-1))
		line->buffer[i + 1] = line->buffer[i];
}

inline void	move_rest_of_buff_to_left(t_line *line)
{
	size_t	i;

	i = line->index;
	while (++i < line->count)
		line->buffer[i - 1] = line->buffer[i];
}

inline bool	delete_char(t_line *line, t_env *env)
{
	if (set_edit_buffer(line, env))
		return (true);
	if (((line->curr_char == RETURN || line->curr_char == CTRL_RETURN)
		&& !line->index)
		|| ((line->curr_char == DEL || line->curr_char == CTRL_DEL)
		&& line->index == line->count))
		return (false);
	line->index -= (line->curr_char == RETURN
		|| line->curr_char == CTRL_RETURN);
	move_rest_of_buff_to_left(line);
	line->count--;
	return (false);
}