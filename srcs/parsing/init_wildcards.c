/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:05:56 by almighty          #+#    #+#             */
/*   Updated: 2026/01/15 14:32:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../includes/parsing.h"

static inline bool	add_to_file_list(char *file_name, char **dst,
	size_t *max_wildcards_len, t_env *env)
{
	size_t	file_len;

	file_len = 0;
	while (file_name[file_len])
		file_len++;
	if (safe_challoc(dst, file_len, env))
		return (true);
	*max_wildcards_len += file_len + 1;
	while (--file_len != (size_t)(-1))
		(*dst)[file_len] = file_name[file_len];
	return (false);
}

static inline bool	safe_opendir(DIR **dir, t_env *env)
{
	*dir = opendir(".");
	if (!*dir)
	{
		create_error("opendir()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

static inline bool	get_file_list(char ***file_list, t_env *env)
{
	DIR				*dir;
	struct dirent	*file;
	size_t			len;

	if (safe_opendir(&dir, env))
		return (true);
	file = readdir(dir);
	len = 0;
	while (file)
	{
		file = readdir(dir);
		len++;
	}
	closedir(dir);
	return (safe_lalloc(file_list, len, env));
}

bool	init_wildcards(t_cmd_parsing *cmdp, t_env *env)
{
	DIR				*dir;
	struct dirent	*file;
	char			**file_list;
	size_t			max_wildcards_len;

	if (get_file_list(&file_list, env)
		|| safe_opendir(&dir, env))
		return (true);
	cmdp->file_list = file_list;
	max_wildcards_len = 0;
	file = readdir(dir);
	while (file)
	{
		if (add_to_file_list(file->d_name, file_list, &max_wildcards_len, env))
			return (true);
		file = readdir(dir);
		file_list++;
	}
	return (safe_challoc(&cmdp->wildcards_str, max_wildcards_len, env));
}
