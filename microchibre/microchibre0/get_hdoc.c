/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:55:49 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 10:46:22 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	open_hdoc(char *del, int *write_fd,
	bool has_expand, t_env *env)
{
	bool	res;
	size_t	i;
	char	*input;
	
	input = NULL;
	while (!get_line(&input, "> ", env) && !is_end_of_hdoc(input, del))
	{
		i = -1;
		while (input[++i])
		{
			if (is_var(input, ' '))
				print_expand(&input, *write_fd, env);
			else
				write(*write_fd, input, 1);
		}
	}
	safe_close(write_fd);
	return (safe_free(&input));
}

static inline size_t	del_len(char *del, bool *has_quotes)
{
	size_t	len;
	char	sep;

	*has_quotes = false;
	len = 0;
	sep = ' ';
	while (!is_end_of_arg(*del, sep))
	{
		if (((sep == ' ') && is_quote(*del)) || sep == *del)
		{
			set_sep(&sep, *del);
			*has_quotes = true;
		}
		else
			len++;
		del++;
	}
	return (len);
}

static inline bool	get_del(char **del, char **dst,
	bool *has_quotes, t_env *env)
{
	size_t	i;
	char	sep;

	if (safe_challoc(dst, del_len(*del, has_quotes), env))
		return (true);
	sep = ' ';
	i = 0;
	while (!is_end_of_arg(**del, sep))
	{
		if (((sep == ' ') && is_quote(*del)) || sep == *del)
		{
			set_sep(&sep, *del);
			*has_quotes = true;
		}
		else
			(*dst)[i++] = **del;
		(*del)++;
	}
	return (false);
}

bool	get_hdoc(char **hdoc, t_cmd *dst, t_env *env)
{
	char	*del;
	bool	del_has_quotes;
	int		hdoc_fds[2];

	(*hdoc) += 2;
	del = NULL;
	hdoc_fds[P_READ] = -1;
	hdoc_fds[P_WRITE] = -1;
	skip_spaces(hdoc);
	if (get_del(hdoc, &del, &del_has_quotes, env) || pipe(hdoc_fds)
		|| open_hdoc(del, hdoc_fds + P_WRITE, del_has_quotes, env))
	{
		safe_close(hdoc_fds + P_READ);
		safe_close(hdoc_fds + P_WRITE);
		safe_free(&del);
		return (true);
	}
	safe_close(&dst->fd_in);
	dst->fd_in = hdoc_fds[P_READ];
	safe_close(hdoc_fds + P_READ);
	safe_close(hdoc_fds + P_WRITE);
	safe_free(&del);
	return (false);
}
