/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 10:16:19 by allmighty         #+#    #+#             */
/*   Updated: 2025/08/27 10:19:32 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_malloc(void **ptr, ssize_t size)
{
	if (size == -1)
		return (1);
	*ptr = malloc(size);
	if (!*ptr)
		return (1);
	return (0);
}

int	set_calloc(char ***ptr, size_t len)
{
	size_t	i;

	*ptr = malloc(sizeof(char *) * (len + 1));
	if (!*ptr)
		return (1);
	i = -1;
	while (++i <= len)
		(*ptr)[i] = NULL;
	return (0);
}

int	env_init(t_env *env, char **envp, int cmd_count)
{
	if (set_calloc(&env->cmd_list, cmd_count))
		return (1);
}