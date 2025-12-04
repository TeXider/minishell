/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:10:11 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 21:29:56 by almighty         ###   ########.fr       */
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

bool	handle_pipes(t_cmd *cmd, t_cmd *next_cmd, t_env *env);

/* PATH */

bool	get_path(t_cmd *cmd, t_env *env);

/* REDIRS */

bool	safe_dup(int dup_fd, int *dst, t_env *env);
bool	dup2_std(int new_std_in, int new_std_out, t_env *env);
bool	set_redirs(t_cmd *cmd, t_env *env);
void	reset_redirs(t_cmd *cmd_list, size_t cmd_list_i, t_env *env);

/* UTILS */

bool	is_end_of_exec(size_t cmd_list_i, size_t cmd_list_len, t_env *env);

#endif