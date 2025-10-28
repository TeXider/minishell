/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 09:09:13 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static inline bool	handle_get_line_error(t_env *env)
{
	return (env != NULL);
}

static inline void	move_index(t_line *line, int term_cols, t_env *env)
{
	move_cursor((line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0), line->index,
		term_cols, env);
	line->index += (line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0);
}

static inline bool	add_curr_char(t_line *line, t_env *env)
{
	int	term_cols;
	
	if (get_term_cols(&term_cols, env))
		return (true);
	if (line->index == line->count)	
	{
		line->buffer[line->index] = line->curr_char;
		write(1, &line->curr_char, 1);
		write(1, "\n",
			get_curr_col(line->index, term_cols, env) == term_cols - 1);
		line->index++;
		line->count++;
	}
	else
	{
		env->debug = 0;
		reset_line_output(line, term_cols, env);
		move_rest_of_buff_to_right(line);
		line->buffer[line->index] = line->curr_char;
		line->index++;
		line->count++;
		env->debug = 1;
		show_line_output(line, term_cols, env);
	}
	return (/*set_correct_line_len(line, env)*/false);
}

// static inline bool	handle_special_char(t_line **line, t_env *env)
// {
// 	int	term_cols;
	
// 	if (get_term_cols(&term_cols, env))
// 		return (true);
// 	if (line->curr_char == ESC_CHAR || line->reading_esc_seq)
// 		get_esc_seqline;
// 	else if (line->curr_char == RETURN)
// 		delete_char(line, CURR_CHAR
// 			| (JUMP * (line->curr_char == CTRL_RETURN)), env);
// 	else if (line->curr_char == ARROW_UP)
// 		history_prev(line, env);
// 	else if (line->curr_char == ARROW_DOWN)
// 		history_next(line, env);
// 	else if (line->curr_char == ARROW_RIGHT)
// 		move_index_right(*line, env);
// 	else if (line->curr_char == ARROW_LEFT)
// 		move_index_left(*line, env);
// 	else if (line->curr_char == DEL)
// 		delete_char(line, NEXT_CHAR | (JUMP * (line->curr_char == CTRL_DEL)),
// 			env);
// 	else if (line->curr_char == '\r')
// 		write(1, "\n", 1);
// 	return (false);
// }

static inline void	delete_char(t_line *line, int term_cols, t_env *env)
{
	if (!line->index)
		return ;
	reset_line_output(line, term_cols, env);
	line->index--;
	move_rest_of_buff_to_left(line);
	line->count--;
	show_line_output(line, term_cols, env);
}

static inline void	get_esc_seq(t_line *line)
{
	char	seq[4];

	read(0, seq, 3);
	if (seq[1] == 'D')
		line->curr_char = ARROW_LEFT;
	else if (seq[1] == 'C')
		line->curr_char = ARROW_RIGHT;
}

static inline void	end_line(t_line *line, int term_cols, t_env *env)
{
	line->index = line->count;
	line->curr_char = '\n';
	move_cursor(line->count - line->index, line->index, term_cols, env);
	add_curr_char(line, env);
	line->curr_char = '\r';
}

static inline bool	handle_special_char(t_line *line, t_env *env)
{
	int	term_cols;

	if (get_term_cols(&term_cols, env))
		return (true);
	if (line->curr_char == '\x1b')
		get_esc_seq(line);
	if (line->curr_char == RETURN)
		delete_char(line, term_cols, env);
	else if (line->curr_char == ARROW_RIGHT
		|| line->curr_char == ARROW_LEFT)
		move_index(line, term_cols, env);
	else if (line->curr_char == '\r')
		end_line(line, term_cols, env);
	return (false);
}

static inline void	print_str(char *str)
{
	while (*str)
		write(1, str++, 1);
}

bool	get_line(char **dst, char *prompt, t_env *env)
{
	t_line	*line;

	if (init_get_line(&line, env))
		return (true);
	print_str(prompt);
	while (line->curr_char != '\r')
	{
		if (read(0, &line->curr_char, 1) == -1)
			return (create_error("read()", SYS_ERR, env)
				| handle_get_line_error(env));
		if (is_special_char(line->curr_char))
		{
			if (handle_special_char(line, env))
				return (handle_get_line_error(env));
		}
		else if (/*(line->next && !line->alter_version
				&& set_alter_version(env))
				|| */add_curr_char(line, env))
				return (handle_get_line_error(env));
	}
	line->buffer[line->count] = '\0';
	*dst = line->buffer;
	return (false);
}
