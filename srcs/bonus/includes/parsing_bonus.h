/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:55:43 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:03:06 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "raboushell_bonus.h"

# define IS_HDOC	-1

typedef struct s_cmd_parsing
{
	char	*str;
	char	*saved_str;
	bool	in_expand;
	t_cmd	*cmd;
	size_t	redirv_i;
	size_t	argv_i;
	size_t	argv_len;
	t_redir	*curr_redir;
	bool	fd_in_is_hdoc;
	char	*curr_arg;
	char	sep;
}	t_cmd_parsing;

/* PARSING */

bool	check_shell_parsing(char **line, bool is_in_subshell, t_env *env);
bool	get_shell_line(char *line, t_shell_op **shell_op, t_env *env);
bool	get_cmd(t_cmd **cmd, char **line, t_env *env);

/* ARGV AND REDIRV */

bool	get_argv_redirv(t_cmd_parsing *cmdp, t_env *env);

/* ARGS */

bool	get_arg(t_cmd_parsing *cmdp, t_env *env);

/* EXPAND */

void	expand(t_cmd_parsing *cmdp, t_env *env);
void	exit_expand(t_cmd_parsing *cmdp);
bool	is_var(t_cmd_parsing *cmdp);
bool	is_end_of_expand(t_cmd_parsing *cmdp);

/* REDIRS */

bool	get_redir_name_len(t_cmd_parsing *cmdp, size_t *len, bool is_hdoc,
			t_env *env);
bool	get_redir(t_cmd_parsing *cmdp, t_env *env);
bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env);
void	safe_close(int *fd, int new_fd);

/* GO TO END OF */

bool	go_to_end_of_arg(t_cmd_parsing *cmdp, t_env *env);
int		go_to_end_of_redir(t_cmd_parsing *cmdp, t_env *env);

/* UTILS */

bool	is_end_of_shell(char *line, bool is_subshell);
bool	is_end_of_cmd(t_cmd_parsing *cmdp);
bool	is_end_of_arg(t_cmd_parsing *cmdp);
bool	is_end_of_redir(t_cmd_parsing *cmdp);
bool	is_quote(char c);
void	set_sep(t_cmd_parsing *cmdp);
void	skip_spaces(char **str);
void	simple_init_cmd_parsing(t_cmd_parsing *cmdp);
void	init_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd, char *line);
bool	change_of_sep(t_cmd_parsing *cmdp);
bool	is_end_of_hdoc(char *del, char *line);
bool	str_eq(char *str1, char *str2);
void	reset_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd);
bool	get_raw_arg(char **dst, t_cmd_parsing *cmdp, bool put_in_quotes,
			t_env *env);
bool	is_control_op(char *str);
bool	is_end_of_line(char *str);
void	remove_redundant_subshells(t_shell_op *shell_op);

#endif