#include "../minishell.h"

int	main(int argc, char **argv)
{
	(void) argc;

	t_env env;
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller="; env.envp[1] = "kiri=123456"; env.envp[2] = "fort=rin tin tin ";
	env.err = 0;
	char *var = convert_export_to_var(argv[1], atoi(argv[2]), atoi(argv[3]), &env);
	if (!var)
		write(1, "wadahelli", 10);
	else
		while (*var)
			write(1, var++, 1);
	write(1, "\n", 1);
}