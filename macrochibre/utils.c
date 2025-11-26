/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:38:44 by almighty          #+#    #+#             */
/*   Updated: 2025/11/26 11:39:52 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_raboushell(void)
{
	write(2, BOLD"["RST GREEN"rabou"RST BOLD SGREEN"shell"RST BOLD"] "RST, 48);
}