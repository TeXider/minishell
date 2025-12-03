/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:24:12 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 20:47:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# include <sys/ioctl.h>
# include "raboushell.h"

# define LINE_LEN 5 
# define ESC_CHAR 27
# define RETURN 127
# define ARROW_UP -1
# define ARROW_DOWN -2
# define ARROW_RIGHT -3
# define ARROW_LEFT -4
# define DEL -5
# define CTRL_RETURN '\027'
# define CTRL_DEL -7
# define CTRL_ARROW -8
# define LEFT -1
# define RIGHT 1
# define CTRL_D '\004'

bool	end_get_line(t_line *line, char **dst, t_gl *env);
bool	is_special_key(char c);
void	safe_free_line(t_line **line);
bool	dup_line(t_line *src, t_line **dst, t_gl *env);
bool	safe_line_alloc(t_line **line, size_t len, t_gl *env);
bool	safe_history_alloc(t_hist **history, t_gl *env);
void	safe_free_history(t_gl *env);
int		curr_col(size_t index, int term_cols, t_gl *env);
bool	get_term_cols(int *term_cols, t_gl *env);
void	move_cursor(ssize_t distance, size_t index, int term_cols, t_gl *env);
void	rewrite_line(t_line *line, int term_cols, t_gl *env);
bool	get_line(char **dst, char *prompt, t_gl *env);
bool	delete_char(t_line **line, t_gl *env);
bool	handle_keys(t_line **line, t_gl *env);
void	handle_lr_arrows(t_line *line, int term_cols, t_gl *env);
bool	add_char(t_line **line, t_gl *env);
bool	handle_ctrl(t_line **line, int term_cols, t_gl *env);
size_t	print_strl(char *str);
void	cpy_str(char *src, char *dst, size_t len);
void	handle_get_line_error(t_gl *env);
bool	new_history_entry(t_gl *env);
void	remove_new_history_entry(t_gl *env);
bool	overwrite_new_history_entry(t_line *line, t_gl *env);
bool	update_history(t_line *line, t_gl *env);
void	move_in_history(t_line **line, int term_cols, t_gl *env);
void	go_to_last_history_entry(t_gl *env);
bool	set_edit_line(t_line **line, t_gl *env);
void	reset_line(t_line *line);

#endif