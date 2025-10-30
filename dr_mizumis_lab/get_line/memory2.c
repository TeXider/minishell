/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:15:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 12:49:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_history_alloc(t_hist **history, t_env *env)
{
	*history = malloc(sizeof(t_hist));
	if (!*history)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_challoc(&(*history)->buffer, LINE_LEN, env))
	{
		free(*history);
		return (create_error("malloc()", SYS_ERR, env));
	}
	(*history)->len = LINE_LEN;
	(*history)->count = 0;
	(*history)->edit_buffer = NULL;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (false);
}