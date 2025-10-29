/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:24:12 by almighty          #+#    #+#             */
/*   Updated: 2025/10/29 10:35:04 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/ioctl.h>

# define STD_IN 0
# define STD_OUT 1
# define FD_ERR 2
# define FD_NULL -1
# define P_READ 0
# define P_WRITE 1
# define CULPRIT_LENGTH 32
# define LINE_LEN 1024 
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

typedef struct termios t_term;
typedef unsigned short int	t_usint;

typedef enum e_err
{
	SYS_ERR,
	TERM_ERR,
	FILE_ERR,
	CLOSE_ERR,
	AMBI_REDIR_ERR,
	UNCLOSED_QUOTES_ERR,
	UNEXPECTED_TOKEN_ERR
}	t_err;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	int		fd_in;
	int		fd_out;
	bool	append_mode;
}	t_cmd;

typedef struct s_line
{
	char			curr_char;
	char			*buffer;
	size_t			index;
	size_t			count;
	size_t			len;
	struct s_line	*next;
	struct s_line	*prev;
	struct s_line	*alter_version;
}	t_line;

typedef struct s_env
{
	char	**envp;
	char	empty_string[1];
	char	*empty_list[2];
	t_term	old_term;
	t_term	term;
	t_line	*history;
	size_t	prompt_len;
	int		win_cols;
	t_err	err;
	char	culprit[CULPRIT_LENGTH];
	bool	is_ctrl;
}	t_env;

bool	create_error(char *culprit, t_err err, t_env *env);
bool	init_get_line(t_line **line, char **dst, t_env *env);
bool	set_alter_version(t_line **line, t_env *env);
bool	end_get_line(t_line *line, char **dst, t_env *env);
bool	is_special_char(char c);
void	move_rest_of_buff_to_right(t_line *line);
void	move_rest_of_buff_to_left(t_line *line);
bool	safe_challoc(char **dst, size_t len, t_env *env);
bool	safe_line_alloc(t_line **line, size_t len, t_env *env);
bool	set_correct_line_len(t_line *line, t_env *env);
char	*create_truncated_buff(t_line *line, t_env *env);
int		get_curr_col(size_t index, int term_cols, t_env *env);
bool	get_term_cols(int *term_cols, t_env *env);
void	move_cursor(ssize_t distance, size_t index, int term_cols, t_env *env);
void	reset_line_output(t_line *line, int term_cols, t_env *env);
void	show_line_output(t_line *line, int term_cols, t_env *env);
bool	get_line(char **dst,  char *prompt, t_env *env);
void	handle_lr_arrows(t_line *line, int term_cols, t_env *env);
void	delete_char(t_line *line);
bool	get_esc_seq(t_line *line, t_env *env);
bool	handle_special_char(t_line **line, t_env *env);
bool	add_curr_char(t_line *line, t_env *env);
size_t	get_jump_len(t_line *line, int dir);
void	handle_ctrl(t_line *line, int term_cols, t_env *env);
size_t	print_strl(char *str);
void	clean_charray(char *arr, size_t len);
bool	handle_get_line_error(t_line *line, t_env *env);
void	end_line(t_line *line, int term_cols, t_env *env);

#endif