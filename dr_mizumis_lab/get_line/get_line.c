/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:23:11 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 13:59:29 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"

bool	init_get_line(t_env *env)
{
	if (!isatty(FD_IN))
		return (create_error("FD_IN is not a TTY", TERM_ERR, env));
	if (tcgetattr(FD_IN, &env->old_term))
		return (create_error("tcgetattr()", TERM_ERR, env));
	env->term = env->old_term;
	env->term.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(FD_IN, TCSANOW, &env->term))
		return (create_error("tcsetattr()", TERM_ERR, env));
	return (false);
}

// bool	get_line(char **dst, char *prompt, t_env *env)
// {
// 	t_term	tmp_term;
// 	t_term	curr_term;
	
	
// }