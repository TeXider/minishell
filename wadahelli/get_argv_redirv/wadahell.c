#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_env
{
	char	**envp;
	char	*empty_string;
	char	**empty_list;
}	t_env;

typedef struct s_cmd_parsing
{
	char	*str;
	char	*saved_str;
	size_t	argv_len;
	size_t	redirv_len;
	char	sep;
}	t_cmd_parsing;

void	set_sep(t_cmd_parsing *cmdp)
{
	cmdp->sep += (!cmdp->saved_str) *
		((' ' - cmdp->sep) * (*(cmdp->str) == cmdp->sep)
		+ (*(cmdp->str) - cmdp->sep)
		* (cmdp->sep == ' ' && (*(cmdp->str) == '\'' || *(cmdp->str) == '"')));
}

bool	is_end_of_cmd(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '\0' || (cmdp->sep == ' '
		&& (*(cmdp->str) == '|' || *(cmdp->str) == '\n')));
}

bool	is_end_of_arg(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '\0' || (cmdp->sep == ' '
		&& (*(cmdp->str) == ' ' || *(cmdp->str) == '>' || *(cmdp->str) == '<'
			|| is_end_of_cmd(cmdp))));
}

bool	go_to_end_of_arg(t_cmd_parsing *cmdp)
{
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		cmdp->str++;
	}
	return (false);
}

void	skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

bool	go_to_end_of_redir(t_cmd_parsing *cmdp)
{
	cmdp->str += 1 + ((*(cmdp->str) == '>' && *(cmdp->str + 1) == '>')
			|| (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<'));
	skip_spaces(&cmdp->str);
	return (go_to_end_of_arg(cmdp));
}

bool	is_var_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

bool	is_var(t_cmd_parsing *cmdp)
{
	return (*(cmdp->str) == '$' && cmdp->sep != '\''
		&& is_var_char(*(cmdp->str + 1)));
}

static bool	check_var_eq(char **str, char **var)
{
	bool	res;

	res = true;
	while (is_var_char(**str))
	{
		res &= (**var == **str);
		(*var) += (**var != '=');
		(*str)++;
	}
	res &= (**var == '=');
	(*var)++;
	return (res);
}

void	exit_expand(t_cmd_parsing *cmdp)
{
	cmdp->str = cmdp->saved_str;
	cmdp->saved_str = NULL;
}

void	expand(t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;
	char	*var;
	size_t	i;

	cmdp->str += (*(cmdp->str) == '$');
	tmp_str = cmdp->str;
	i = -1;
	while (!cmdp->saved_str && env->envp[++i])
	{
		var = env->envp[i];
		cmdp->str = tmp_str;
		if (check_var_eq(&cmdp->str, &var))
		{
			if (!*var)
				return ;
			cmdp->saved_str = cmdp->str;
			cmdp->str = var;
		}
	}
}

static bool	go_through_arg(t_cmd_parsing *cmdp, t_env *env)
{
	bool	is_empty;

	is_empty = true;
	cmdp->sep = ' ';
	while (!is_end_of_arg(cmdp))
	{
		set_sep(cmdp);
		if (!cmdp->saved_str && cmdp->sep != '"' && is_var(cmdp))
			expand(cmdp, env);
		else
		{
			is_empty &= (*(cmdp->str) == ' ');
			cmdp->str++;
		}
		if (cmdp->saved_str && !*(cmdp->str))
			exit_expand(cmdp);
	}
	return (is_empty);
}

bool	get_argv_redirv(t_cmd_parsing *cmdp, t_env *env)
{
	char	*tmp_str;

	tmp_str = cmdp->str;
	while (cmdp->saved_str || !is_end_of_cmd(cmdp))
	{
		if (!cmdp->saved_str && (*(cmdp->str) == '>' || *(cmdp->str) == '<'))
		{
			go_to_end_of_redir(cmdp);
			cmdp->redirv_len++;
		}
		else if (*(cmdp->str) != ' ')
			cmdp->argv_len += !go_through_arg(cmdp, env);
		else
			cmdp->str++;
		if (cmdp->saved_str && !*(cmdp->str))
			exit_expand(cmdp);
	}
	cmdp->str = tmp_str;
	return (false);
}

int	main(int argc, char **argv)
{
	(void) argc; (void) argv;
	char *empty_list[2];
	t_env	env;
	empty_list[0] = NULL; empty_list[1] = NULL;
	env.empty_list = empty_list;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller=   c "; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=fra ka ka ";
	t_cmd_parsing cmdp;
	cmdp.argv_len = 0;
	cmdp.redirv_len = 0;
	cmdp.saved_str = NULL;
	cmdp.sep = ' ';
	cmdp.str = malloc(sizeof(char) * 257);
	ssize_t rd = read(1, cmdp.str, 256);
	if (rd == -1)
		return (1);
	cmdp.str[rd] = '\0';
	get_argv_redirv(&cmdp, &env);
	printf("argv_len : %zu, redirv_len : %zu\n", cmdp.argv_len, cmdp.redirv_len);
}