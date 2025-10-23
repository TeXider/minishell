/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:35:25 by almighty          #+#    #+#             */
/*   Updated: 2025/10/23 08:54:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	move_rest_of_buff_to_right(t_line *line)
{
	size_t	i;

	i = line->count;
	while (--i >= line->index)
		line->buffer[i] = line->buffer[i - 1];
}

inline bool	delete_char(t_line **line, t_env *env)
{
	
}