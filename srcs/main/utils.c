/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:38:44 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 11:56:29 by tpanou-d         ###   ########.fr       */
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
	env->exit_code_str[0] = env->exit_code / 100 + '0';
	env->exit_code_str[1] = (env->exit_code / 10) % 10 + '0';
	env->exit_code_str[2] = env->exit_code % 10 + '0';
}