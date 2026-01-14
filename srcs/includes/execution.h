/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:10:11 by almighty          #+#    #+#             */
/*   Updated: 2026/01/14 13:02:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "raboushell.h"

typedef struct s_exec
{
	t_shell_op		*shell_op;
	int				pipe_fds[2][2];
	size_t			pipe_index;
	int				*pipe_fd_read;
	int				*pipe_fd_write;
	bool			is_child;
	t_cmd			*prev_cmd;
	t_shell_op_type	prev_op;
	int				children_count;
	pid_t			last_pid;
	int				saved_std_in;
	int				saved_std_out;
}	t_exec;

/* EXECUTION */

void	exec_shell_op_line(t_shell_op *shell_op, t_env *env);
void	exec_cmd(t_cmd *cmd, t_exec *exec, t_env *env);

/* PIPES */

void	close_pipes(t_exec *exec);
bool	open_pipe(t_exec *exec, t_env *env);

/* PATH */

bool	get_path(t_cmd *cmd, t_env *env);

/* REDIRS */

bool	save_std_fds(t_exec *exec, t_env *env);
bool	dup2_std(int new_std_in, int new_std_out, t_env *env);
bool	open_cmd_redirs(t_cmd *cmd, t_env *env);
bool	set_redirs_to_std(t_cmd *cmd, t_exec *exec, t_env *env);

/* UTILS */

void	init_exec(t_exec *exec, t_shell_op *shell_op);
bool	is_end_of_exec(t_exec *exec, t_env *env);
bool	has_to_exec(t_exec *exec, t_env *env);
bool	get_path_var(char **path_var, t_env *env);
bool	handle_fork(t_exec *exec, t_env *env);
void	wait_children(t_exec *exec, t_env *env);

#endif