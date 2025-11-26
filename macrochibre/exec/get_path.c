/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:41:55 by almighty          #+#    #+#             */
/*   Updated: 2025/11/26 11:27:38 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline void	get_join_path_lens(size_t *path_len, size_t *name_len,
	char *path, char *name)
{
	*path_len = 0;
	*name_len = 0;
	while ((path[*path_len] && path[*path_len] != ':') || name[*name_len])
	{
		*path_len += (path[*path_len] && path[*path_len] != ':');
		*name_len += (name[*name_len] != '\0');
	}
}

static inline bool	join_path(char **path_dst, char **path_var, char *cmd_name,
	t_env *env)
{
	size_t	path_len;
	size_t	name_len;
	size_t	i;

	*path_var += (**path_var == ':' && *(*path_var - 1) != '=');
	get_join_path_lens(&path_len, &name_len, *path_var, cmd_name);
	if (!path_len)
	{
		*path_dst = cmd_name;
		return (false);
	}
	if (safe_challoc(path_dst, path_len + name_len + 1, env))
		return (true);
	i = -1;
	while (++i < path_len + name_len + (path_len != 0))
	{
		if (i < path_len)
			(*path_dst)[i] = (*path_var)[i];
		else if (path_len && i == path_len)
			(*path_dst)[i] = '/';
		else
			(*path_dst)[i] = cmd_name[i - (path_len != 0) - path_len];
	}
	*path_var += path_len;
	return (false);
}

static inline bool	get_path_var(char **path_var, t_env *env)
{
	size_t	i;

	i = -1;
	while (env->envp[++i])
	{
		if (env->envp[i][0] == 'P'
			&& env->envp[i][1] == 'A'
			&& env->envp[i][2] == 'T'
			&& env->envp[i][3] == 'H'
			&& env->envp[i][4] == '=')
		{
			*path_var = env->envp[i] + 5;
			return (**path_var == '\0');
		}
	}
	return (true);
}

bool	get_path(t_cmd *cmd, t_env *env)
{
	char	*path_var;

	if (cmd->cmd_name_is_path
		|| get_path_var(&path_var, env))
	{
		cmd->path = cmd->argv[0];
		return (false);
	}
	while (*path_var)
	{
		if (join_path(&cmd->path, &path_var, cmd->argv[0], env))
			return (true);
		if (!access(cmd->path, F_OK | X_OK))
			return (false);
		if (cmd->path != cmd->argv[0])
			free(cmd->path);
	}
	create_error(cmd->argv[0], EXEC_ERR, env);
	return (true);
}
