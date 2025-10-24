# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/ioctl.h>

bool	move_cursor(int distance, int *curr_col, int win_col)
{
	size_t	i;

	while (distance)
	{
		if ((distance < 0 && *curr_col == 0) || (distance > 0 && *curr_col + 1 == win_col))
		{
			write(1, "\x1b[A\x1b[B" + 3 * (distance > 0 && *curr_col + 1 == win_col),
				3);
			i = -1;
			while (++i < win_col)
				write(1, "\x1b[C\x1b[D" + 3 * (distance > 0), 3);
		}
		else
			write(1, "\x1b[C\x1b[D" + 3 * (distance < 0), 3);
		*curr_col = (*curr_col + (1 - 2 * (distance < 0)));
		*curr_col += (win_col) * (*curr_col < 0);
		*curr_col %= win_col;
		distance += 1 - 2 * (distance > 0);
	}
}

int main()
{
	struct termios	term;
	struct winsize	win;
	char			c;
	int			col;

	ioctl(0, TIOCGWINSZ, &win);
	tcgetattr(0, &term);
	term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	tcsetattr(0, TCSANOW, &term);
	col = 0;
	int win_col = win.ws_col;
	write(1, "\n\n\n\n\n\n\n", 7);
	while (read(0, &c, 1))
	{
		if (c == 'a')
			move_cursor(-1, &col, win_col);
		else
			move_cursor(1, &col, win_col);
	}
}