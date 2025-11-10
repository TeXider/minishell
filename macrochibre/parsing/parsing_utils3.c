/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:40:22 by almighty          #+#    #+#             */
/*   Updated: 2025/11/10 13:49:45 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline bool	str_eq(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == *str2);
}

inline void	safe_close(int *fd)
{
	if (*fd != STD_IN && *fd != STD_OUT && *fd != FD_ERR && *fd != FD_NULL)
	{
		close(*fd);
		*fd = FD_NULL;
	}
}