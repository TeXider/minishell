/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:17:31 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/12/01 09:47:47 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

inline void	handle_lr_arrows(t_line *line, int term_cols, t_gl *env)
{
	move_cursor((line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0), line->index,
		term_cols, env);
	line->index += (line->curr_char == ARROW_RIGHT && line->index < line->count)
		- (line->curr_char == ARROW_LEFT && line->index > 0);
}

static inline bool	get_esc_seq(t_line *line, t_gl *env)
{
	int		rd;
	size_t	i;
	char	seq[7];

	i = -1;
	while (++i < 7)
		seq[i] = false;
	rd = read(0, seq, 6);
	if (rd == -1)
	{
		create_error("read()", SYS_ERR, env->main_env);
		return (true);
	}
	line->curr_char = ARROW_LEFT * (seq[1] == 'D' || seq[4] == 'D')
		+ ARROW_RIGHT * (seq[1] == 'C' || seq[4] == 'C')
		+ ARROW_UP * (seq[1] == 'A') + ARROW_DOWN * (seq[1] == 'B')
		+ DEL * (seq[1] == '3' && seq[2] == '~')
		+ CTRL_DEL * (seq[0] == 'd');
	env->is_ctrl = ((seq[1] == '1' && seq[2] == ';') || (seq[0] == 'd'));
	return (false);
}

static inline bool	handle_special_keys(t_line **line, int term_cols,
		t_gl *env)
{
	if ((*line)->curr_char == '\033' && get_esc_seq(*line, env))
		return (true);
	if (env->is_ctrl || (*line)->curr_char == CTRL_RETURN)
	{
		if (handle_ctrl(line, term_cols, env))
			return (true);
	}
	else if ((*line)->curr_char == DEL || (*line)->curr_char == RETURN)
	{
		if (delete_char(line, env))
			return (true);
		rewrite_line(*line, term_cols, env);
	}
	else if ((*line)->curr_char == ARROW_RIGHT
		|| (*line)->curr_char == ARROW_LEFT)
		handle_lr_arrows((*line), term_cols, env);
	else if ((*line)->curr_char == ARROW_UP
		|| (*line)->curr_char == ARROW_DOWN)
		move_in_history(line, term_cols, env);
	else if ((*line)->curr_char == '\r')
		write(1, "\n", 1);
	return (false);
}

bool	handle_keys(t_line **line, t_gl *env)
{
	int	term_cols;

	if (get_term_cols(&term_cols, env))
		return (true);
	if (is_special_key((*line)->curr_char))
	{
		if (handle_special_keys(line, term_cols, env))
			return (true);
	}
	else
	{
		if (add_char(line, env))
			return (true);
		rewrite_line(*line, term_cols, env);
	}
	return (false);
}
