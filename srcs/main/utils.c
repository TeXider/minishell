/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:38:44 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 14:06:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

inline void	print_raboushell(void)
{
	write(2, BOLD"["RST GREEN"rabou"RST BOLD SGREEN"shell"RST BOLD"] "RST, 48);
}

inline void	print_str(char *str)
{
	while (*str)
		write(1, str++, 1);
}

inline void	set_exit_code(t_uchar exit_code, t_env *env)
{
	env->exit_code = exit_code;
	env->exit_code_str[0] = exit_code / 100 + '0';
	env->exit_code_str[1] = (exit_code / 10) % 10 + '0';
	env->exit_code_str[2] = exit_code % 10 + '0';
}

inline void	safe_close(int *fd, int new_fd)
{
	if (*fd != STD_IN && *fd != STD_OUT && *fd != FD_ERR && *fd != FD_NULL)
	{
		close(*fd);
		*fd = new_fd;
	}
}
