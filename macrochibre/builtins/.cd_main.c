#include <stdio.h>
#include "../minishell.h"

int	main(int argc, char **argv)
{
	t_env	env;
	
	(void) argc;
	env.exportp = malloc(sizeof(char *));
	env.exportp[0] = NULL;
	env.exportp_len = 0;
	env.envp = malloc(sizeof(char *));
	env.envp[0] = NULL;
	env.envp_len = 0;
	builtin_cd(argv + 1, &env);
	char *dir = getcwd(NULL, 0);
	builtin_export(& (char *) { NULL }, &env);
	printf("%s\n", dir);
	free(env.exportp[0]);
	free(env.exportp[1]);
	free(env.exportp);
	free(env.envp);
	free(dir);
}