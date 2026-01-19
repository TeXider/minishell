/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:35:29 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:02:22 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_line_bonus.h"

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

inline size_t	print_prompt(char *str)
{
	bool	in_esc_seq;
	size_t	len;
	size_t	printed_len;

	in_esc_seq = false;
	len = 0;
	printed_len = 0;
	while (str[len])
	{
		in_esc_seq |= (str[len] == '\e');
		printed_len += !in_esc_seq;
		len += 1 + (str[len + 1] == 'm' && in_esc_seq);
		in_esc_seq &= (str[len - (len > 0)] != 'm');
	}
	write(1, str, len);
	return (printed_len);
}

inline void	cpy_str(char *src, char *dst, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
}
