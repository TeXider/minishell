/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/15 11:43:18 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	free_data(t_cmd *cmd, char *line, t_env *env)
{
	(void) env;
	if (cmd)
	{
		if (cmd->path)
			free(cmd->path);
		if (cmd->argv)
			free(cmd->argv);
	}
	if (line)
		free(line);
}

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (create_error(NULL, SYS_ERR, env));
	(*dst)[len] = '\0';
	return (false);
}

inline bool	safe_lalloc(char ***dst, size_t len, t_env *env)
{
	if (!len)
		*dst = env->empty_list;
	else
	{
		*dst = malloc(sizeof(char *) * (len + 1));
		if (!*dst)
			return (create_error(NULL, SYS_ERR, env));
		(*dst)[0] = NULL;
	}
	return (false);
}

inline bool	safe_cmdlalloc(t_cmd **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(t_cmd) * (len + 1));
	if (!*dst)
		return (create_error(NULL, SYS_ERR, env));
	set_new_cmd(*dst + len, env);
	return (false);
}
