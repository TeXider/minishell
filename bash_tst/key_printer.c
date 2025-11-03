/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:48:54 by almighty          #+#    #+#             */
/*   Updated: 2025/10/23 11:51:53 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>

int	MAIn(int argc, char **argv)
{
	char	c;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		if (argc == 1)
		{
			write(1, & (char) { c / 100 + '0' }, 1);
			write(1, & (char) { (c / 10) % 10 + '0'}, 1);
			write(1, & (char) { c % 10 + '0'}, 1);
			if (c >= ' ' && c <= '~')
				write(1, "\t\"", 2) + write(1, &c, 1) + write(1, "\"", 1);
			write(1, "\n────────────\n", 39);
		}
		else
		{
			if (c == 127)
				write(1, "\b \b", 3);
			else
				write(1, &c, 1);
		}
	}
	return (0);
}
