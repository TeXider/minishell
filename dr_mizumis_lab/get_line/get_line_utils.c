/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:35:29 by almighty          #+#    #+#             */
/*   Updated: 2025/10/22 12:33:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_line_alloc(t_line **line, t_env *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
		return (create_error("malloc()", SYS_ERR, env));
	(*line)->len = LINE_SIZE;
	(*line)->count = 0;
	(*line)->index = 0;
	(*line)->curr_char = '\0';
}

inline bool	init_get_line(t_line **line, t_env *env)
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
	if (safe_line_alloc(line, env))
		return (true);
	return (false);
}

inline bool	switch_line_version(t_line **line, t_env *env)
{
	if (!(*line)->alter_version)
	{ 
		if (safe_line_alloc(&(*line)->alter_version, env))
			return (true);
		(*line)->alter_version->next = (*line)->next;
		(*line)->alter_version->prev = (*line)->prev;
		(*line)->alter_version->alter_version = *line;
		*line = (*line)->alter_version;
	}
	return (false);
}

inline bool	end_get_line(t_line **line, t_env *env)
{
	if (tcsetattr(FD_IN, TCSANOW, &env->old_term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	return (false);
}

inline bool	is_special_char(char c)
{
	return (c < ' ' || c > '~');
}