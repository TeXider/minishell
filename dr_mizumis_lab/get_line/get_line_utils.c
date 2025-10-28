/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:35:29 by almighty          #+#    #+#             */
/*   Updated: 2025/10/28 17:18:36 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

inline bool	is_special_char(char c)
{
	return (c < ' ' || c > '~');
}

inline int	get_curr_col(size_t index, int term_cols, t_env *env)
{
	return ((index + env->prompt_len) % term_cols);
}

inline bool	get_term_cols(int *term_cols, t_env *env)
{
	struct winsize	win;

	if (ioctl(STD_IN, TIOCGWINSZ, &win))
		return (create_error("ioctl()", SYS_ERR, env));
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

inline void	clean_charray(char *arr, size_t len)
{
	while (--len)
		arr[len] = '\0';
}
