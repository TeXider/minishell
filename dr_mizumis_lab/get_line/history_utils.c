/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:09:57 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/31 11:36:06 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	go_to_last_history_entry(t_env *env)
{
	while (env->history->next)
		env->history = env->history->next;
}

inline bool	set_edit_line(t_line **line, t_env *env)
{
	if (env->history->next && env->history->og_line != env->history->edit_line)
	{
		if (safe_line_alloc(&env->history->edit_line,
			env->history->og_line->len, env))
			return (true);
		cpy_str(env->history->og_line->buffer, env->history->edit_line->buffer,
			env->history->og_line->len);
		*line = env->history->edit_line;
	}
	return (false);
}
