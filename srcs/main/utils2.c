/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:15:23 by almighty          #+#    #+#             */
/*   Updated: 2025/12/09 12:54:35 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

inline void	print_ushort(t_uint num)
{
	char	res[9];
	int		len;
	int		i;

	len = 1 + (num > 9) + (num > 99) + (num > 999) + (num > 9999)
		+ (num > 99999) + (num > 999999) + (num > 9999999) + (num > 99999999)
		+ (num > 999999999);
	i = len - 1;
	while (i >= 0)
	{
		res[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	write(1, res, len);
}
