#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_iflag &= ~(INLCR | IGNCR | ICRNL);
	term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "chibrax""chibrute", 16);
	write(1, "\r\n", 2);
}