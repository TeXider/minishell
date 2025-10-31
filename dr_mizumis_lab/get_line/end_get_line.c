/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:14:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/31 11:48:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	handle_get_line_error(t_env *env)
{
	write(1, "\n", 1);
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
		create_error("tcsetattr()", TERM_ERR, env);
	remove_new_history_entry(env);
}

static inline char	*create_truncated_buff(t_line *line, t_env *env)
{
	char	*tmp;
	size_t	i;

	if (safe_challoc(&tmp, line->count + 1, env))
		return (NULL);
	i = -1;
	while (++i < line->count)
		tmp[i] = line->buffer[i];
	tmp[line->count] = '\n';
	return (tmp);
}

bool	end_get_line(t_line *line, char **dst, t_env *env)
{
	t_hist	*curr_hist;
	
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
	{
		create_error("tcsetattr()", TERM_ERR, env);
		return (true);
	}
	*dst = create_truncated_buff(line, env);
	if (!*dst)
	{
		remove_new_history_entry(env);
		return (true);
	}
	if (env->history->next)
	{
		curr_hist = env->history;
		overwrite_new_history_entry(line, env);
		curr_hist->edit_line = curr_hist->og_line;
	}
	if (!line->count)
		remove_new_history_entry(env);
	go_to_last_history_entry(env);
	return (false);
}
