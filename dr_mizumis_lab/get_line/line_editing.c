/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:35:25 by almighty          #+#    #+#             */
/*   Updated: 2025/10/29 09:37:49 by tpanou-d         ###   ########.fr       */
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

inline void	delete_char(t_line *line)
{
	if (((line->curr_char == RETURN || line->curr_char == CTRL_RETURN)
		&& !line->index)
		|| ((line->curr_char == DEL || line->curr_char == CTRL_DEL)
		&& line->index == line->count))
		return ;
	line->index -= (line->curr_char == RETURN
		|| line->curr_char == CTRL_RETURN);
	move_rest_of_buff_to_left(line);
	line->count--;
}