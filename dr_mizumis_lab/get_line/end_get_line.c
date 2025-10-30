/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:14:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 11:07:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	handle_get_line_error(t_line *line, t_env *env)
{
	(void) line;
	remove_new_history_entry(env);
	return (true);
}

inline bool	end_get_line(t_line *line, char **dst, t_env *env)
{
	t_hist	*curr_hist;
	
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	*dst = create_truncated_buff(line, env);
	if (!*dst)
		return (handle_get_line_error(line, env));
	if (env->history->next)
	{
		curr_hist = env->history;
		overwrite_new_history_entry(line, env);
		safe_free((void **) &curr_hist->edit_buffer);
	}
	if (line->count == 0)
		remove_new_history_entry(env);
	return (false);
}
