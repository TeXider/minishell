/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:24:12 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 13:51:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>

# define FD_IN 0
# define FD_OUT 1
# define FD_ERR 2
# define FD_NULL -1
# define P_READ 0
# define P_WRITE 1
# define CULPRIT_LENGTH 32

typedef struct termios t_term;

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

typedef struct s_env
{
	char	**envp;
	char	empty_string[1];
	char	*empty_list[2];
	t_term	old_term;
	t_term	term;
	t_err	err;
	char	culprit[CULPRIT_LENGTH];
}	t_env;

bool	init_get_line(t_env *env);
bool	create_error(char *culprit, t_err err, t_env *env);

#endif