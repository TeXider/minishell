/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:16 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

inline bool	is_var(t_cmd_parsing *cmdp)
{
	return (!cmdp->in_expand && (*(cmdp->str) == '$' && cmdp->sep != '\''
			&& (is_var_char(*(cmdp->str + 1)) || *(cmdp->str + 1) == '?')));
}

inline bool	is_end_of_expand(t_cmd_parsing *cmdp)
{
	return (cmdp->in_expand && !*(cmdp->str));
}
