/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/24 10:56:03 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static inline bool	handle_get_line_error(t_env *env)
{
	return (env != NULL);
}

static inline bool	add_curr_char(t_line **line, t_env *env)
{
	int	term_cols;
	
	if (get_term_cols(&term_cols, env))
		return (true);
	if ((*line)->index == (*line)->count)	
	{
		(*line)->buffer[(*line)->index] = (*line)->curr_char;
		(*line)->index++;
		(*line)->count++;
		write(1, &(*line)->curr_char, 1);
	}
	else
	{
		reset_line_output(*line, term_cols, env);
		move_rest_of_buff_to_right(*line);
		(*line)->buffer[(*line)->index] = (*line)->curr_char;
		(*line)->index++;
		(*line)->count++;
		show_line_output(*line, term_cols, env);
	}
	return (/*set_correct_line_len(line, env)*/false);
}
// static inline bool	handle_special_char(t_line **line, t_env *env)
// {
// 	if ((*line)->curr_char == ESC_CHAR || (*line)->reading_esc_seq)
// 		get_esc_seq(*line);
// 	else if ((*line)->curr_char == RETURN)
// 		delete_char(line, CURR_CHAR
// 			| (JUMP * ((*line)->curr_char == CTRL_RETURN)), env);
// 	else if ((*line)->curr_char == ARROW_UP)
// 		history_prev(line, env);
// 	else if ((*line)->curr_char == ARROW_DOWN)
// 		history_next(line, env);
// 	else if ((*line)->curr_char == ARROW_RIGHT)
// 		move_index_right(*line, env);
// 	else if ((*line)->curr_char == ARROW_LEFT)
// 		move_index_left(*line, env);
// 	else if ((*line)->curr_char == DEL)
// 		delete_char(line, NEXT_CHAR | (JUMP * ((*line)->curr_char == CTRL_DEL)),
// 			env);
// 	else if ((*line)->curr_char == '\r')
// 		write(1, "\n", 1);
// 	return (false);
// }

// static inline bool	handle_special_char(t_line **line, t_env *env)
// {
// 	if ((*line)->curr_char == RETURN)
// 		delete_char(line, env);
// 	else if ((*line)->curr_char == '\r')
// 		write(1, "\n", 1);
// 	return (false);
// }

bool	get_line(char **dst, char *prompt, t_env *env)
{
	t_line	*line;

	if (init_get_line(&line, env))
		return (true);
	(void) prompt;//print_str(prompt);
	while (line->curr_char != '\r')
	{
		if (read(0, &line->curr_char, 1) == -1)
			return (create_error("read()", SYS_ERR, env)
				| handle_get_line_error(env));
		// if (is_special_char(line->curr_char))
		// {
		// 	if (handle_special_char(&line, env))
		// 		return (handle_get_line_error(env));
		// }
		// else
			if (/*(line->next && !line->alter_version
				&& set_alter_version(env))
				|| */line->curr_char != '\r' && add_curr_char(&line, env))
				return (handle_get_line_error(env));
	}
	line->buffer[line->count] = '\0';
	*dst = line->buffer;
	return (false);
}
