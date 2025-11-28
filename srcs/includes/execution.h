/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:10:11 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 13:15:36 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "raboushell.h"

typedef struct s_pipes
{
	int		pipe_fds[2];
	int		next_pipe_fds[2];
	bool	is_next_pipe;
	int		fd_read;
	int		fd_write;
}	t_pipes;

/* PIPES */

bool	repipe(int pipes_fds[2], bool is_last_cmd, t_env *env);
void	init_pipes(t_pipes *pipes);
void	close_pipes(t_pipes *pipes);
bool	handle_pipes(t_pipes *pipes, size_t cmd_list_i, size_t cmd_list_len,
			t_env *env);

/* PATH */

bool	get_path(t_cmd *cmd, t_env *env);

/* REDIRS */

bool	open_redirs(t_cmd *cmd, t_env *env);

#endif