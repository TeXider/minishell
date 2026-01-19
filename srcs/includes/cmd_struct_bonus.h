/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:09:09 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:53 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H

# include "raboushell_bonus.h"

typedef enum e_builtin
{
	NOT_BUILTIN,
	CD_BUILTIN,
	ECHO_BUILTIN,
	ENV_BUILTIN,
	EXIT_BUILTIN,
	EXPORT_BUILTIN,
	PWD_BUILTIN,
	UNSET_BUILTIN
}	t_builtin;

typedef enum e_rtype
{
	EMPTY_REDIR,
	HDOC,
	IN,
	OUT,
	APPND,
	AMBI_REDIR
}	t_rtype;

typedef struct s_redir
{
	char	*name;
	t_rtype	type;
}	t_redir;

typedef struct s_cmd
{
	char		*path;
	bool		cmd_name_is_path;
	char		**argv;
	t_redir		*redirv;
	size_t		redirv_len;
	int			fd_in;
	int			fd_out;
	bool		is_fd_in_hdoc;
	t_builtin	builtin;
}	t_cmd;

typedef enum e_shell_op_type
{
	EMPTY_OP,
	PIPE_OP,
	AND_OP,
	OR_OP
}	t_shell_op_type;

typedef struct s_shell_op
{
	void				*op;
	bool				is_subshell;
	t_shell_op_type		op_type;
	struct s_shell_op	*next;
}	t_shell_op;

#endif