/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:38:44 by almighty          #+#    #+#             */
/*   Updated: 2025/11/28 14:00:50 by almighty         ###   ########.fr       */
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