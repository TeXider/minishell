#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int pid = fork();
	if (!pid)
	{
		execve("inf_loop", argv, envp);
	}
	int ec;
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT,&sa, NULL);
	waitpid(pid, &ec, 0);
	if (WIFEXITED(ec))
		ec = WEXITSTATUS(ec);
	else if (WIFSIGNALED(ec))
		ec = 128 + WTERMSIG(ec);
	printf("%d: %s\n", ec, strerror(ec));
}