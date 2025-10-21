/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/21 18:36:31 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	init_get_line(t_env *env)
{
	if (!isatty(FD_IN))
		return (create_error("FD_IN is not a TTY", TERM_ERR, env));
	if (tcgetattr(FD_IN, &env->old_term))
		return (create_error("tcgetattr()", TERM_ERR, env));
	env->term = env->old_term;
	env->term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	env->term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	if (tcsetattr(FD_IN, TCSANOW, &env->term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	if (create_history_entry(env))
		return (true);
	env->line->count = LINE_SIZE;
	env->line->buffer[0] = '\0';
	env->line->curr_char = '\0';
	return (false);
}

inline bool	end_get_line(t_line *line, t_env *env)
{
	safe_free(line->buffer);
	return (true);
}

inline bool	get_line(char **dst, char *prompt, t_env *env)
{
	if (init_get_line(env))
		return (true);
	print_str(prompt);
	while (env->line->curr_char != '\r')
	{
		if (read(0, &env->line->curr_char, 1) == -1)
			return (create_error("read()", SYS_ERR, env)
				| handle_get_line_error(env));
		else if (is_special_char(env->line->curr_char))
		{
			if (handle_special_char(env))
				return (handle_get_line_error(env));
		}
		else
		{
			if (add_curr_char(env))
				return (handle_get_line_error(env));
			write(1, &env->line->curr_char, 1);
		}
	}
	*dst = env->line->buffer;
	return (false);
}
/*
	when starting get_line, copy-on-write history
	until execution. Then, add the new entry to history and restore
	env->line to history
*/