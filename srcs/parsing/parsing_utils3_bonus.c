/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:40:22 by almighty          #+#    #+#             */
/*   Updated: 2026/01/14 13:08:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

inline bool	str_eq(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == *str2 || (*str1 == '\n' && !*str2)
		|| (!*str1 && *str2 == '\n'));
}

inline void	reset_cmd_parsing(t_cmd_parsing *cmdp, t_cmd *cmd)
{
	cmdp->saved_str = NULL;
	cmdp->sep = ' ';
	cmdp->in_expand = false;
	cmdp->argv_len = 0;
	cmdp->redirv_i = 0;
	cmdp->argv_i = 0;
	cmdp->cmd = cmd;
}

inline bool	is_control_op(char *str)
{
	return (*str == '|' || (*str == '&' && *(str + 1) == '&'));
}

inline bool	is_end_of_line(char *str)
{
	return (!*str || *str == '\n');
}
