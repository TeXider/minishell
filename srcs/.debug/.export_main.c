#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc; (void) argv; (void) envp;
	t_env env;
	env.exportp = malloc(sizeof(char *));
	env.exportp[0] = NULL;
	env.exportp_len = 0;
	env.envp = malloc(sizeof(char *));
	env.envp[0] = NULL;
	env.envp_len = 0;
	builtin_export(argv + 1, &env);
	print_export(&env);
	free(env.exportp);
}