/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/11/13 14:28:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline void	safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

inline void	free_data(t_cmd *cmd, char *line, t_env *env)
{
	if (cmd)
	{
		if (cmd->path)
			free(cmd->path);
		if (cmd->argv)
			free(cmd->argv);
	}
	if (line)
		free(line);
	if (env->envp)
		free(env->envp);
}

inline bool	safe_malloc(void **dst, size_t len, t_env *env)
{
	if (!len)
	{
		*dst = NULL;
		return (false);
	}
	*dst = malloc(len);
	if (!*dst)
	{
		create_error("malloc()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
	{
		create_error("malloc()", SYS_ERR, env);
		return (true);
	}
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
		{
			create_error("malloc()", SYS_ERR, env);
			return (true);
		}
		(*dst)[0] = NULL;
		(*dst)[len] = NULL;
	}
	return (false);
}
