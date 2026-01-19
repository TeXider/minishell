/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:40:22 by almighty          #+#    #+#             */
/*   Updated: 2025/12/08 10:06:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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

inline bool	get_raw_arg(char **dst, t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;
	size_t	i;

	i = 0;
	tmp_str = cmdp->str;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		cmdp->str++;
		i++;
	}
	if (safe_challoc(dst, i, env))
		return (true);
	cmdp->str = tmp_str;
	i = 0;
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		(*dst)[i++] = *(cmdp->str++);
	}
	return (false);
}

inline void	set_new_cmd(t_cmd *cmd)
{
	cmd->path = NULL;
	cmd->cmd_name_is_path = false;
	cmd->argv = NULL;
	cmd->redirv = NULL;
	cmd->redirv_len = 0;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
	cmd->is_fd_in_hdoc = false;
}
