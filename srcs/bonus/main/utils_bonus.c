/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:38:44 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:03 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell_bonus.h"

inline void	print_raboushell(void)
{
	write(2, BOLD"["RABOU"rabou"SHELL"shell"RST BOLD"] "RST, 48);
}

inline void	print_str(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
}

inline void	set_exit_code(t_uchar exit_code, t_env *env)
{
	t_uint	len;

	env->exit_code = exit_code;
	len = 1 + (exit_code > 9) + (exit_code > 99);
	env->exit_code_str[len - 1] = exit_code % 10 + '0';
	env->exit_code_str[len - 2 * (len > 1)] = (exit_code / 10) % 10 + '0';
	env->exit_code_str[len - 3 * (len > 2)] = (exit_code / 100) % 10 + '0';
	env->exit_code_str[len] = '\0';
}

inline void	safe_close(int *fd, int new_fd)
{
	if (*fd != STD_IN && *fd != STD_OUT && *fd != FD_ERR && *fd != FD_NULL)
	{
		close(*fd);
		*fd = new_fd;
	}
}

inline bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}
