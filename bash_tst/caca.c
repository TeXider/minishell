#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	access("ls", X_OK);
	perror(NULL);
	printf("%d\n", errno);
}