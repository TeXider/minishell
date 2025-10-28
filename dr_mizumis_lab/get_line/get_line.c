/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 10:23:13 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static inline bool	handle_get_line_error(t_env *env)
{
	return (env != NULL);
}

static inline void	handle_lr_arrows(t_line *line, int term_cols, t_env *env)
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
	if ((line->curr_char == RETURN && !line->index)
		|| (line->curr_char == DEL && line->index == line->count))
		return ;
	reset_line_output(line, term_cols, env);
	line->index -= (line->curr_char == RETURN);
	if ((line->curr_char == RETURN))
		move_rest_of_buff_to_left(line);
	else
	{
		line->index++;
		move_rest_of_buff_to_left(line);
		line->index--;
	}
	line->count--;
	show_line_output(line, term_cols, env);
}

static inline bool	get_esc_seq(t_line *line, t_env *env)
{
	char	seq[4];

	if (read(0, seq, 3) == -1)
		return (create_error("read()", SYS_ERR, env));
	line->curr_char = ARROW_LEFT * (seq[1] == 'D')
		+ ARROW_RIGHT * (seq[1] == 'C')
		+ ARROW_UP * (seq[1] == 'A')
		+ ARROW_DOWN * (seq[1] == 'B')
		+ DEL * (seq[1] == '3' && seq[2] == '~');
	return (false);
}

static inline void	end_line(t_line *line, int term_cols, t_env *env)
{
	line->index = line->count;
	line->curr_char = '\n';
	move_cursor(line->count - line->index, line->index, term_cols, env);
	add_curr_char(line, env);
	line->curr_char = '\r';
}

static inline bool	handle_special_char(t_line **line, t_env *env)
{
	int	term_cols;

	if (get_term_cols(&term_cols, env))
		return (true);
	if ((*line)->curr_char == '\x1b')
	{
		if (get_esc_seq(*line, env))
			return (true);
	}
	if ((*line)->curr_char == DEL || (*line)->curr_char == RETURN)
		delete_char(*line, term_cols, env);
	else if ((*line)->curr_char == ARROW_RIGHT
		|| (*line)->curr_char == ARROW_LEFT)
		handle_lr_arrows(*line, term_cols, env);
	else if ((*line)->curr_char == ARROW_UP || (*line)->curr_char == ARROW_DOWN)
		/*move_in_history(line, term_cols, env)*/;
	else if ((*line)->curr_char == '\r')
		end_line(*line, term_cols, env);
	return (false);
}

static inline size_t	print_strl(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		write(1, str[len++], 1);
	return (len);
}

bool	get_line(char **dst, char *prompt, t_env *env)
{
	t_line	*line;

	if (init_get_line(&line, env))
		return (true);
	env->prompt_len = print_strl(prompt);
	while (line->curr_char != '\r')
	{
		if (read(0, &line->curr_char, 1) == -1)
			return (create_error("read()", SYS_ERR, env)
				| handle_get_line_error(env));
		if (is_special_char(line->curr_char))
		{
			if (handle_special_char(&line, env))
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
