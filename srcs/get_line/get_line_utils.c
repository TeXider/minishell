/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:35:29 by almighty          #+#    #+#             */
/*   Updated: 2025/12/03 11:22:20 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line.h"

inline bool	is_special_key(char c)
{
	return (c < ' ' || c > '~');
}

inline int	curr_col(size_t index, int term_cols, t_gl *env)
{
	return ((index + env->prompt_len) % term_cols);
}

inline bool	get_term_cols(int *term_cols, t_gl *env)
{
	struct winsize	win;

	if (ioctl(STD_IN, TIOCGWINSZ, &win))
	{
		create_error("ioctl()", TERM_ERR, env->main_env);
		return (true);
	}
	*term_cols = win.ws_col;
	return (false);
}

inline size_t	print_strl(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		write(1, str + len++, 1);
	return (len);
}

inline void	cpy_str(char *src, char *dst, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
}
