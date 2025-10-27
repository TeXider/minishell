/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:35:29 by almighty          #+#    #+#             */
/*   Updated: 2025/10/27 13:46:00 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	is_special_char(char c)
{
	return (c < ' ' || c > '~');
}

inline bool	init_get_line(t_line **line, t_env *env)
{
	if (!isatty(STD_IN))
		return (create_error("FD_IN is not a TTY", TERM_ERR, env));
	if (tcgetattr(STD_IN, &env->old_term))
		return (create_error("tcgetattr()", TERM_ERR, env));
	env->term = env->old_term;
	env->term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	env->term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	if (tcsetattr(STD_IN, TCSANOW, &env->term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	if (safe_line_alloc(line, LINE_SIZE, env))
		return (true);
	return (false);
}

// inline bool	switch_line_version(t_line **line, t_env *env)
// {
// 	if (!(*line)->alter_version)
// 	{ 
// 		if (safe_line_alloc(&(*line)->alter_version, (*line)->len, env))
// 			return (true);
// 		(*line)->alter_version->next = (*line)->next;
// 		(*line)->alter_version->prev = (*line)->prev;
// 		(*line)->alter_version->alter_version = *line;
// 		*line = (*line)->alter_version;
// 	}
// 	return (false);
// }

// inline bool	end_get_line(t_line **line, t_env *env)
// {
// 	if (tcsetattr(STD_IN, TCSANOW, &env->old_term))
// 		return (create_error("tcsetattr()", TERM_ERR, env));
// 	return (false);
// }

inline int	get_curr_col(size_t index, int term_cols, t_env *env)
{
	return ((index + env->prompt_len) % term_cols);
}

inline bool	get_term_cols(int *term_cols, t_env *env)
{
	struct winsize	win;

	if (ioctl(STD_IN, TIOCGWINSZ, &win))
		return (create_error("ioctl()", SYS_ERR, env));
	*term_cols = win.ws_col;
	return (false);
}