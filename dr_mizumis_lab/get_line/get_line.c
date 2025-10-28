/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 16:32:33 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

static inline bool	handle_get_line_error(t_line *line, t_env *env)
{
	free(line->buffer);
	free(line);
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

static inline size_t	get_jump_len(t_line *line, int dir)
{
	size_t	len;
	size_t	i;

	len = 1;
	i = line->index + dir;
	while (i > 0 && i < line->count
		&& !(dir == LEFT && line->buffer[i] != ' '
		&& line->buffer[i - 1] == ' ')
		&& !(dir == RIGHT && line->buffer[i] == ' '
		&& line->buffer[i - 1] != ' '))
	{
		len++;
		i += dir;
	}
	return (len);
}

static inline void	delete_char(t_line *line, int term_cols, t_env *env)
{
	if ((line->curr_char == RETURN && !line->index)
		|| (line->curr_char == DEL && line->index == line->count))
		return ;
	reset_line_output(line, term_cols, env);
	line->index -= (line->curr_char == RETURN);
	move_rest_of_buff_to_left(line);
	line->count--;
	show_line_output(line, term_cols, env);
}

static inline void	handle_ctrl(t_line *line, int term_cols, t_env *env)
{
	size_t	i;
	size_t	jump_len;
	
	env->is_ctrl = false;
	if (!line->count)
		return ;
	jump_len = get_jump_len(line, LEFT * (line->curr_char == ARROW_LEFT
		|| line->curr_char == CTRL_RETURN)
		+ RIGHT * (line->curr_char == ARROW_RIGHT
		|| line->curr_char == CTRL_DEL));
	i = -1;
	while (++i < jump_len)
	{
		if (line->curr_char == ARROW_LEFT || line->curr_char == ARROW_RIGHT)
			handle_lr_arrows(line, term_cols, env);
		else if (line->curr_char == CTRL_DEL || line->curr_char == CTRL_RETURN)
		{
			line->curr_char = DEL * (line->curr_char == CTRL_DEL)
				+ RETURN * (line->curr_char == CTRL_RETURN);
			delete_char(line, term_cols, env);
			line->curr_char = CTRL_DEL * (line->curr_char == DEL)
				+ CTRL_RETURN * (line->curr_char == RETURN);
		}
	}
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
		reset_line_output(line, term_cols, env);
		move_rest_of_buff_to_right(line);
		line->buffer[line->index] = line->curr_char;
		line->index++;
		line->count++;
		show_line_output(line, term_cols, env);
	}
	return (/*set_correct_line_len(line, env)*/false);
}

static inline void	clean_charray(char *arr, size_t len)
{
	while (--len)
		arr[len] = '\0';
}

static inline bool	get_esc_seq(t_line *line, t_env *env)
{
	char	seq[7];

	clean_charray(seq, 7);
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
	if ((*line)->curr_char == '\033')
	{
		if (get_esc_seq(*line, env))
			return (true);
	}
	if (env->is_ctrl || (*line)->curr_char == CTRL_RETURN)
		handle_ctrl(*line, term_cols, env);
	else if ((*line)->curr_char == DEL || (*line)->curr_char == RETURN)
		delete_char(*line, term_cols, env);
	else if ((*line)->curr_char == ARROW_RIGHT
		|| (*line)->curr_char == ARROW_LEFT)
		handle_lr_arrows(*line, term_cols, env);
	else if ((*line)->curr_char == ARROW_UP || (*line)->curr_char == ARROW_DOWN)
		/*move_in_history(line, term_cols, env)*/(void) env;
	else if ((*line)->curr_char == '\r')
		end_line(*line, term_cols, env);
	return (false);
}

static inline size_t	print_strl(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		write(1, str + len++, 1);
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
	line->buffer[line->count] = '\0'; //truncate_line()
	//add_history(); -> necessary because of line_alter_version
	*dst = line->buffer;
	return (false);
}
