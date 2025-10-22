#include <termios.h>
#include <unistd.h>

int main()
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	char	c;
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		write(1, & (char) { c / 100 + '0' }, 1);
		write(1, & (char) { (c / 10) % 10 + '0'}, 1);
		write(1, & (char) { c % 10 + '0'}, 1);
		write(1, "\n", 1);
	}
	return (0);
}