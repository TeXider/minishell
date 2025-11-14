/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:41:55 by almighty          #+#    #+#             */
/*   Updated: 2025/11/14 14:38:39 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (*path_var == '\0');
		}
	}
	return (true);
}

bool	get_path(t_cmd *cmd, t_env *env)
{
	char	*path_var;
	char	*path;
	
	if (cmd->cmd_name_is_path
		|| get_path_var(&path_var, env))
	{
		cmd->path = cmd->argv[0];
		return (false);
	}
	while (*path_var)
	{
		if (join_path(&path, cmd->argv[0]))
			return (true);
		if (access(path, O_EXCL))
			return (true);
		//blah blah blah i'm DONE FOR THE WEEK YEEEEE
	}
}