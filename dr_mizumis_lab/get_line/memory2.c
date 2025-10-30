/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:15:13 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/30 13:52:07 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_history_alloc(t_hist **history, t_env *env)
{
	*history = malloc(sizeof(t_hist));
	if (!*history)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_line_alloc(&(*history)->edit_line, LINE_LEN, env))
	{
		free(*history);
		return (create_error("malloc()", SYS_ERR, env));
	}
	(*history)->edit_line->len = LINE_LEN;
	(*history)->edit_line->count = 0;
	(*history)->og_line = (*history)->edit_line;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (false);
}