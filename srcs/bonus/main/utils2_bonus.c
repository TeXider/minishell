/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 21:15:23 by almighty          #+#    #+#             */
/*   Updated: 2026/01/16 15:04:06 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell_bonus.h"

inline void	print_uint(t_uint num)
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
