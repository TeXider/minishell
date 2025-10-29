/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:14:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/29 10:30:16 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	handle_get_line_error(t_line *line, t_env *env)
{
	free(line->buffer);
	free(line);
	return (env != NULL);
}

inline void	end_line(t_line *line, int term_cols, t_env *env)
{
	line->index = line->count;
	line->curr_char = '\n';
	move_cursor(line->count - line->index, line->index, term_cols, env);
	add_curr_char(line, env);
	line->curr_char = '\r';
}

inline bool	end_get_line(t_line *line, char **dst, t_env *env)
{
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
 		return (create_error("tcsetattr()", TERM_ERR, env));
	*dst = create_truncated_buff(line, env);
	if (!*dst)
		return (true);
	if (!line->alter_version && line->count == 0)
	 	remove_new_history_entry(env);
	return (false);
}
