#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

// int	main()
// {
// 	pid_t	caca;
// 	char *release_me = malloc(sizeof(char));
// 	caca = fork();
// 	if (!caca)
// 	{
// 		exit(0);
// 	}
// 	free(release_me);
// 	return (0);
// }

#define DUMMY abc

int main(int argc, char **argv, char **envp)
{
	char	c;

	while (1)
		read(1, &c, 1);
}
