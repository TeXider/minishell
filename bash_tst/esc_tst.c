/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_tst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:06:45 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/26 13:16:08 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	buff[256];
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", 17);
	size_t	i;
	char	res;
	while (1)
	{
		i = 0;
		res = 1;
		while (res)
		{
			res = read(STDIN_FILENO, buff + i, 1);
			i += res;
		}
		if (i)
			write(1, buff, i + 1);
	}
}