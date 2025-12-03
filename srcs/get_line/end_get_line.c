/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_get_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:14:17 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/12/03 11:17:25 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline char	*create_truncated_buff(t_line *line, t_gl *env)
{
	char	*tmp;
	size_t	i;

	if (safe_challoc(&tmp, line->count + 1, env->main_env))
		return (NULL);
	i = -1;
	while (++i < line->count)
		tmp[i] = line->buffer[i];
	tmp[line->count] = '\n';
	return (tmp);
}

bool	end_get_line(t_line *line, char **dst, t_gl *env)
{
	reset_line(line);
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
	{
		create_error("tcsetattr()", TERM_ERR, env->main_env);
		return (true);
	}
	*dst = create_truncated_buff(line, env);
	if (!*dst)
	{
		remove_new_history_entry(env);
		return (true);
	}
	return (update_history(line, env));
}

void	handle_get_line_error(t_gl *env)
{
	write(1, "\n", 1);
	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
		create_error("tcsetattr()", TERM_ERR, env->main_env);
	remove_new_history_entry(env);
}
