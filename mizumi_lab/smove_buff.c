#include <stdlib.h>
#include <unistd.h>

void	move_rest_of_buff_to_right(char *buf, int index, int count)
{
	int	i;

	i = count;
	while (--i >= index)
		buf[i + 1] = buf[i];
}

int main(int argc, char **argv)
{
	int count;
	int i;
	char buf[256];
	i=-1;
	count = 0;
	while (argv[1][++i])
	{
		buf[i]=argv[1][i];
		count++;
	}
	move_rest_of_buff_to_right(buf, atoi(argv[2]), count);
	buf[atoi(argv[2])] = argv[3][0];
	buf[count + 1] = '\0';
	for (i = 0; buf[i]; i++)
		write(1, buf + i, 1);
	write(1, "\n", 1);
}