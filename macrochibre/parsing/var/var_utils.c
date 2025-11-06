/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2025/11/06 10:08:10 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

inline bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

inline bool	is_var(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '$' && cmdp->sep != '\''
		&& is_var_char(*(cmdp->str + 1)));
}
