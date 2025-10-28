/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:35:25 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 08:45:02 by almighty         ###   ########.fr       */
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