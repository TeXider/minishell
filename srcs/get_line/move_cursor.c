/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:43:31 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 14:26:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

static inline t_uchar	itoa_len(int num)
{
	t_uchar	res;

	res = 1;
	while (num > 9)
	{
		num /= 10;
		res++;
	}
	return (res);
}

static inline t_uchar	get_col_esc_seq(char *esc_seq, ssize_t distance,
	int col, int term_cols)
{
	t_uchar	len;
	ssize_t	new_col;
	char	dir;
	t_uchar	i;

	new_col = (distance + col) % term_cols;
	new_col += term_cols * (new_col < 0);
	if (new_col == col)
		return (0);
	dir = 'D' + ('C' - 'D') * (new_col > col);
	distance = (col - new_col) * (1 - 2 * (col - new_col < 0));
	len = itoa_len(distance) + 2;
	i = -1;
	while (++i < len - 2)
	{
		esc_seq[len - 1 - i] = distance % 10 + '0';
		distance /= 10;
	}
	esc_seq[len] = dir;
	return (len + 1);
}

static inline int	compute_row_distance(ssize_t distance, int col,
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

static inline t_uchar	get_row_esc_seq(char *esc_seq, ssize_t distance,
	int col, int term_cols)
{
	t_uchar	len;
	int		row_distance;
	char	dir;
	t_uchar	i;

	row_distance = compute_row_distance(distance, col, term_cols);
	if (!row_distance)
		return (0);
	dir = 'A' + ('B' - 'A') * (distance > 0);
	len = itoa_len(row_distance) + 2;
	i = -1;
	while (++i < len - 2)
	{
		esc_seq[len - 1 - i] = row_distance % 10 + '0';
		row_distance /= 10;
	}
	esc_seq[len] = dir;
	return (len + 1);
}

void	move_cursor(ssize_t distance, size_t index, int term_cols,
	t_gl *env)
{
	int		col;
	char	esc_seq[8];
	t_uchar	esc_seq_len;

	if (!distance)
		return ;
	col = curr_col(index, term_cols, env);
	esc_seq[0] = '\e';
	esc_seq[1] = '[';
	esc_seq_len = get_row_esc_seq(esc_seq, distance, col, term_cols);
	write(1, esc_seq, esc_seq_len);
	esc_seq_len = get_col_esc_seq(esc_seq, distance, col, term_cols);
	write(1, esc_seq, esc_seq_len);
}
