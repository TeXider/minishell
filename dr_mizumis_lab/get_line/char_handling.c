/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:17:31 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/29 12:21:52 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline void	handle_lr_arrows(t_line *line, int term_cols, t_env *env)
{
	move_cursor((line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0), line->index,
		term_cols, env);
	line->index += (line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0);
}

inline bool	get_esc_seq(t_line *line, t_env *env)
{
	size_t	i;
	char	seq[7];

	i = -1;
	while (++i < 7)
		seq[i] = false;
	if (read(0, seq, 6) == -1)
		return (create_error("read()", SYS_ERR, env));
	line->curr_char = ARROW_LEFT * (seq[1] == 'D' || seq[4] == 'D')
		+ ARROW_RIGHT * (seq[1] == 'C' || seq[4] == 'C')
		+ ARROW_UP * (seq[1] == 'A')
		+ ARROW_DOWN * (seq[1] == 'B')
		+ DEL * (seq[1] == '3' && seq[2] == '~')
		+ CTRL_DEL * (seq[0] == 'd');
	env->is_ctrl = ((seq[1] == '1' && seq[2] == ';') || (seq[0] == 'd'));
	return (false);
}

inline bool	handle_special_char(t_line **line, t_env *env)
{
	int	term_cols;

	if (get_term_cols(&term_cols, env))
		return (true);
	if ((*line)->curr_char == '\033')
	{
		if (get_esc_seq(*line, env))
			return (true);
	}
	if (env->is_ctrl || (*line)->curr_char == CTRL_RETURN)
		handle_ctrl(*line, term_cols, env);
	else if ((*line)->curr_char == DEL || (*line)->curr_char == RETURN)
	{
		reset_line_output(*line, term_cols, env);
		delete_char(*line);
		show_line_output(*line, term_cols, env);
	}
	else if ((*line)->curr_char == ARROW_RIGHT
		|| (*line)->curr_char == ARROW_LEFT)
		handle_lr_arrows(*line, term_cols, env);
	else if ((*line)->curr_char == ARROW_UP || (*line)->curr_char == ARROW_DOWN)
		move_in_history(line, term_cols, env);
	else if ((*line)->curr_char == '\r')
		write(1, "\n", 1);
	return (false);
}

inline bool	add_curr_char(t_line *line, t_env *env)
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
		reset_line_output(line, term_cols, env);
		move_rest_of_buff_to_right(line);
		line->buffer[line->index] = line->curr_char;
		line->index++;
		line->count++;
		show_line_output(line, term_cols, env);
	}
	return (set_correct_line_len(line, env));
}