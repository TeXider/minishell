/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:01:12 by almighty          #+#    #+#             */
/*   Updated: 2025/12/18 14:30:01 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	simple_init_cmd_parsing(t_cmd_parsing *cmdp)
{
	cmdp->str = NULL;
	cmdp->saved_str = NULL;
	cmdp->in_expand = false;
	cmdp->sep = ' ';
}

inline void	init_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd, char *line)
{
	cmdp->str = line;
	cmdp->saved_str = NULL;
	cmdp->sep = ' ';
	cmdp->in_expand = false;
	cmdp->argv_len = 0;
	cmdp->redirv_i = 0;
	cmdp->argv_i = 0;
	cmdp->cmd = cmd;
}

inline bool	change_of_sep(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && is_quote(*(cmdp->str))
		&& (cmdp->sep == ' ' || *(cmdp->str) == cmdp->sep));
}

inline bool	is_end_of_redir(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && (*(cmdp->str) == '\0' || (cmdp->sep == ' '
				&& (*(cmdp->str) == ' '
					|| *(cmdp->str) == '>' || *(cmdp->str) == '<'
					|| is_end_of_cmd(cmdp)))));
}

inline bool	is_end_of_hdoc(char *del, char *line)
{
	return (line && str_eq(del, line));
}
