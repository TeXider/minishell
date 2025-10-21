 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:30:42 by allmighty         #+#    #+#             */
/*   Updated: 2025/08/20 15:26:04 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int path_split_malloc(char **str, char **element)
{
	size_t	j;
	
	j = 0;
	while ((*str)[j] && (*str)[j] != ':')
		j++;
	if (set_malloc((void **) element, sizeof(char) * (j + 1)))
		return (1);
	j = -1;
	while ((*str)[++j] && (*str)[j] != ':')
		(*element)[j] = (*str)[j];
	(*element)[j] = '\0';
	*str += j;
	return (0);
}
	
int path_split(char *path, char ***dst, t_env *env)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (path[i] == ':')
		i++;
	while (path[++i])
		len += ((path[i] == ':') && path[i + 1] 
			&& path[i + 1] != ':');
	if (set_calloc(dst, len))
		return (1);
	i = -1;
	while (++i < len)
	{
		while (*path == ':')
			path++;
		if (path_split_malloc(&path, *dst + i))
			return (1);
	}
	return (0);
}
