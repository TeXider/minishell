/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 09:29:35 by almighty          #+#    #+#             */
/*   Updated: 2026/01/15 14:47:08 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

inline bool	is_expand(t_cmd_parsing *cmdp)
{
	t_cmd_parsing	tmp_cmdp;

	if (cmdp->in_expand)
		return (false);
	if (*(cmdp->str) == '$' && cmdp->sep != '\''
			&& (is_var_char(*(cmdp->str + 1)) || *(cmdp->str + 1) == '?'))
		return (true);
	tmp_cmdp = *cmdp;
	while (!is_end_of_arg(&tmp_cmdp))
	{
		set_sep(&tmp_cmdp);
		if (tmp_cmdp.sep == ' ' && *(tmp_cmdp.str) == '*')
			return (true);
		tmp_cmdp.str++;
	}
	return (false);
}

inline bool	is_end_of_expand(t_cmd_parsing *cmdp)
{
	return (cmdp->in_expand && !*(cmdp->str));
}
