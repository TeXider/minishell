/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/12/04 11:56:40 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline bool	init_get_line(t_line **line, char **dst, t_gl *env)
{
	*dst = NULL;
	if (!isatty(STD_IN))
	{
		create_error("isatty()", TERM_ERR, env->main_env);
		return (true);
	}
	if (tcgetattr(STD_IN, &env->old_term))
	{
		create_error("tcgetattr()", TERM_ERR, env->main_env);
		return (true);
	}
	env->term = env->old_term;
	env->term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	env->term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	env->term.c_cc[VMIN]  = 0;
    env->term.c_cc[VTIME] = 1;
	if (tcsetattr(STD_IN, TCSANOW, &env->term))
	{
		create_error("tcsetattr()", TERM_ERR, env->main_env);
		return (true);
	}
	if (new_history_entry(env))
		return (true);
	*line = env->history->edit_line;
	return (false);
}

bool	get_line(char **dst, char *prompt, t_gl *env)
{
	t_line	*line;
	char	read_res;

	if (init_get_line(&line, dst, env))
		return (true);
	env->prompt_len = print_strl(prompt);
	while (!g_sig && line->curr_char != '\r')
	{
		env->prev_line_count = line->count;
		env->prev_line_index = line->index;
		read_res = read(0, &line->curr_char, 1);
		if (read_res == -1)
		{
			create_error("read()", SYS_ERR, env->main_env);
			handle_get_line_error(env);
			return (true);
		}
		if (read_res && handle_keys(&line, env))
		{
			handle_get_line_error(env);
			return (true);
		}
	}
	return (end_get_line(line, dst, env));
}
