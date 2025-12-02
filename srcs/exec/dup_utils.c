/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:02:11 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 17:23:17 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

inline bool	safe_dup(int dup_fd, int *dst, t_env *env)
{
	*dst = dup(dup_fd);
	if (*dst == -1)
	{
		create_error("dup()", SYS_ERR, env);
		return (true);
	}
	return (false);
}

inline bool	dup2_std(int new_std_in, int new_std_out, t_env *env)
{
	if ((new_std_in != FD_NULL && dup2(new_std_in, STD_IN) == -1)
		|| (new_std_out != FD_NULL && dup2(new_std_out, STD_OUT) == -1))
	{
		create_error("dup2()", SYS_ERR, env);
		return (true);
	}
	return (false);
}
