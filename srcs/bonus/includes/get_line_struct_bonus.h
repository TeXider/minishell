/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_struct_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 20:10:39 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:03:03 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_STRUCT_H
# define GET_LINE_STRUCT_H

# include <termios.h>
# include "raboushell_bonus.h"

typedef struct termios		t_term;
typedef unsigned int		t_uint;

typedef struct s_line
{
	char			curr_char;
	char			*buffer;
	size_t			index;
	size_t			count;
	size_t			len;
}	t_line;

typedef struct s_hist
{
	t_line			*edit_line;
	t_line			*og_line;
	struct s_hist	*next;
	struct s_hist	*prev;
}	t_hist;

typedef struct s_gl
{
	t_term	old_term;
	t_term	term;
	t_hist	*history;
	size_t	prompt_len;
	int		win_cols;
	size_t	prev_line_count;
	size_t	prev_line_index;
	bool	update_history;
	bool	is_ctrl;
	t_uint	line_count;
	void	*main_env;
}	t_gl;

#endif