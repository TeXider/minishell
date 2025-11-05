/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2025/11/05 14:11:33 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

inline bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

inline bool	is_var(char *str, char sep)
{
	return (*str == '$' && sep != '\'' && is_var_char(*(str + 1)));
}
