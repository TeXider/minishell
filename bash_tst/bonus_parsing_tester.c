#include "unistd.h"

int main(int argc, char **av)
{
	char	in[512];

	int rd = read(0, in, 512);
	if (!rd)
		write(1, "wadaheli", 9);
	else
		write(1, in, rd);
	char tmp = in[rd - 1] + 1;
	write(1, av[1], 1);
}