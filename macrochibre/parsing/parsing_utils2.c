/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:01:12 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 14:35:22 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline void	init_cmd_parsing(t_cmd_parsing *cmdp, char *line)
{
	cmdp->str = line;
	cmdp->saved_str = NULL;
	cmdp->sep = ' ';
	cmdp->in_expand = false;
	cmdp->argv_len = 0;
	cmdp->redirv_i = 0;
	cmdp->argv_i = 0;
	cmdp->cmd = NULL;
}

inline bool	change_of_sep(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && ((cmdp->sep == ' ' && is_quote(*(cmdp->str)))
		|| *(cmdp->str) == cmdp->sep));
}

inline bool	is_end_of_redir(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && (*(cmdp->str) == '\0' || (cmdp->sep == ' '
		&& (*(cmdp->str) == ' ' || *(cmdp->str) == '>' || *(cmdp->str) == '<'
			|| is_end_of_cmd(cmdp)))));
}