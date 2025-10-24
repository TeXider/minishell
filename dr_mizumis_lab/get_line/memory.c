/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:15:39 by almighty          #+#    #+#             */
/*   Updated: 2025/10/24 09:34:22 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	safe_challoc(char **dst, size_t len, t_env *env)
{
	*dst = malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (create_error(NULL, SYS_ERR, env));
	(*dst)[len] = '\0';
	return (false);
}

inline bool	safe_line_alloc(t_line **line, size_t len, t_env *env)
{
	*line = malloc(sizeof(t_line));
	if (!*line)
		return (create_error("malloc()", SYS_ERR, env));
	if (safe_challoc(&(*line)->buffer, len, env))
		return (create_error("malloc()", SYS_ERR, env));
	(*line)->len = len;
	(*line)->count = 0;
	(*line)->index = 0;
	(*line)->curr_char = '\0';
	return (false);
}
