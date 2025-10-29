/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/29 10:18:35 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	init_get_line(t_line **line, char **dst, t_env *env)
{
	*dst = NULL;
	if (!isatty(STD_IN))
		return (create_error("FD_IN is not a TTY", TERM_ERR, env));
	if (tcgetattr(STD_IN, &env->old_term))
		return (create_error("tcgetattr()", TERM_ERR, env));
	env->term = env->old_term;
	env->term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	env->term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	if (tcsetattr(STD_IN, TCSANOW, &env->term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	if (safe_line_alloc(line, LINE_LEN, env))
		return (true);
	return (false);
}

inline bool	get_line(char **dst, char *prompt, t_env *env)
{
	t_line	*line;

	if (init_get_line(&line, dst, env))
		return (true);
	env->prompt_len = print_strl(prompt);
	while (line->curr_char != '\r')
	{
		if (read(0, &line->curr_char, 1) == -1)
			return (create_error("read()", SYS_ERR, env)
				| handle_get_line_error(line, env));
		if (is_special_char(line->curr_char))
		{
			if (handle_special_char(&line, env))
				return (handle_get_line_error(line, env));
		}
		else if (/*(line->next && !line->alter_version
				&& set_alter_version(&line, env))
				|| */add_curr_char(line, env))
				return (handle_get_line_error(line, env));
	}
	return (end_get_line(line, dst, env));
}
