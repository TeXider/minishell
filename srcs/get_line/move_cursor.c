/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:43:31 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 14:41:21 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline t_uchar	get_col_esc_seq(char *esc_seq, t_sint distance,
	int col, int term_cols)
{
	t_uchar	len;
	t_sint	new_col;
	char	dir;
	t_uchar	i;

	new_col = (distance + col) % term_cols;
	new_col += term_cols * (new_col < 0);
	if (new_col == col)
		return (0);
	dir = 'D' + ('C' - 'D') * (new_col > col);
	distance = (col - new_col) * (1 - 2 * (col - new_col < 0));
	len = 1 + (distance > 9) + (distance > 99) + (distance > 999)
		+ (distance > 9999);
	i = -1;
	while (++i < len)
	{
		esc_seq[len - 1 - i] = distance % 10 + '0';
		distance /= 10;
	}
	esc_seq[len] = dir;
	return (len + 1);
}

static inline int	compute_row_distance(t_sint distance, int col,
	int term_cols)
{
	bool	sgn;
	int		res;

	sgn = distance < 0;
	res = (distance + col < 0 || distance + col >= term_cols);
	distance *= 1 - 2 * sgn;
	distance -= res * ((term_cols - 1 - 2 * col) * !sgn + col);
	return (res + (distance / term_cols));
}

static inline t_uchar	get_row_esc_seq(char *esc_seq, t_sint distance,
	int col, int term_cols)
{
	t_uchar	len;
	char	dir;
	t_uchar	i;

	dir = 'A' + ('B' - 'A') * (distance > 0);
	distance = compute_row_distance(distance, col, term_cols);
	if (!distance)
		return (0);
	len = 1 + (distance > 9) + (distance > 99) + (distance > 999)
		+ (distance > 9999);
	i = -1;
	while (++i < len)
	{
		esc_seq[len - 1 - i] = distance % 10 + '0';
		distance /= 10;
	}
	esc_seq[len] = dir;
	return (len + 1);
}

void	move_cursor(ssize_t distance, size_t index, int term_cols, t_gl *env)
{
	int		col;
	char	esc_seq[8];
	t_uchar	esc_seq_len;
	t_sint	short_distance;

	if (!distance)
		return ;
	if (distance > 32767)
		short_distance = 32767;
	else if (distance < -32768)
		short_distance = -32768;
	else
		short_distance = (t_sint) distance;
	col = curr_col(index, term_cols, env);
	esc_seq[0] = '\e';
	esc_seq[1] = '[';
	esc_seq_len = 2 + get_row_esc_seq(esc_seq + 2, short_distance, col,
			term_cols);
	write(1, esc_seq, esc_seq_len);
	esc_seq_len = 2 + get_col_esc_seq(esc_seq + 2, short_distance, col,
			term_cols);
	write(1, esc_seq, esc_seq_len);
}
