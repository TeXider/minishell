#include "minishell.h"

bool	check_var_empty(char **var_str, t_env *env)
{
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	i = -1;
	while (var.val[++i])
		if (var.val[i] != ' ')
			return (false);
	return (true);
}

bool	check_ambiguous_var(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (true);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
			&& var.val[i + 1] != ' ')
			return (true);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (false);
}

int	check_var_validity(char **var_str, t_env *env)
{
	bool	has_arg;
	char	sep;
	size_t	i;
	t_var	var;

	if (get_var(var_str, &var, env))
		return (1);
	sep = ' ';
	has_arg = false;
	i = -1;
	while (var.val[++i])
	{
		if (has_arg && sep == ' ' && var.val[i] == ' ' && var.val[i + 1]
			&& var.val[i + 1] != ' ')
			return (2);
		has_arg |= (var.val[i] != ' ');
		set_sep(&sep, var.val[i]);
	}
	return (!has_arg);
}

bool	var_contains_spaces(t_var *var)
{
	size_t	i;
	
	if (!var->val)
		return (false);
	i = -1;
	while (var->val[++i])
		if (var->val[i] == ' ')
			return (true);
	return (false);
}
