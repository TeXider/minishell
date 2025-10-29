/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:13:27 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/10/29 09:08:09 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

// inline bool	set_alter_version(t_line **line, t_env *env)
// {
// 	if (safe_line_alloc(&(*line)->alter_version, (*line)->len, env))
// 		return (true);
// 	(*line)->alter_version->next = (*line)->next;
// 	(*line)->alter_version->prev = (*line)->prev;
// 	(*line)->alter_version->alter_version = *line;
// 	*line = (*line)->alter_version;
// 	return (false);
// }