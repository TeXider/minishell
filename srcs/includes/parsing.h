/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:55:43 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:08:51 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "raboushell.h"

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

bool	get_redir_name_len(char *redir, size_t *len, bool is_hdoc, t_env *env);
bool	get_redir(t_cmd_parsing *cmdp, t_env *env);
bool	get_hdoc(t_cmd_parsing *cmdp, bool has_expand, t_env *env);
void	safe_close(int *fd, int new_fd);

/* GO TO END OF */

bool	go_to_end_of_arg(t_cmd_parsing *cmdp, t_env *env);
int		go_to_end_of_redir(t_cmd_parsing *cmdp, t_env *env);
bool	go_to_end_of_cmd(t_cmd_parsing *cmdp, size_t *cmd_list_len,
			bool *is_empty, t_env *env);

/* UTILS */

bool	is_end_of_cmd(t_cmd_parsing *cmdp);
bool	is_end_of_arg(t_cmd_parsing *cmdp);
bool	is_end_of_redir(t_cmd_parsing *cmdp);
bool	is_quote(char c);
void	set_sep(t_cmd_parsing *cmdp);
void	skip_spaces(char **str);
void	simple_init_cmd_parsing(t_cmd_parsing *cmdp);
void	init_cmd_parsing(t_cmd_parsing *cmdp, char *line);
bool	change_of_sep(t_cmd_parsing *cmdp);
bool	is_end_of_hdoc(char *del, char *line);
bool	str_eq(char *str1, char *str2);
void	reset_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd);

#endif