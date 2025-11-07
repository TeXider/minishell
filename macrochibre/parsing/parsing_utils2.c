/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:01:12 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 09:05:25 by almighty         ###   ########.fr       */
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
	cmdp->redirv_len = 0;
	cmdp->cmd = NULL;
}