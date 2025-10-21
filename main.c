/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:55:39 by almighty          #+#    #+#             */
/*   Updated: 2025/09/09 08:15:50 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
	char	*exec;
	char	**argv;
	int		*fd_in;
	int		*fd_out;
	
}	t_cmd;

size_t	get_arg_len(char *arg)
{
	size_t	i;
	char	sep;
	
	sep = ' ' + (*arg == '\'' || *arg == '"') * (*arg - ' ');
	i = -1;
	while (arg[++i] != ' ')
	{
		if (arg[i] == sep)
			sep == ' ';
		else if (sep != '"' && arg[i] == 0)
			;
	}
}

int	get_arg(char **arg, char **dst, size_t i, t_env *env)
{
	char	sep;
	
	sep = ' ' + (**arg == '\'' || **arg == '"') * (**arg - ' ');
	while ()
}

int	cmd_parse(char **cmd_str, t_cmd *dst, t_env *env)
{
	size_t	i;

	if (set_malloc(&(dst->argv), count_args(*cmd_str)))
		return (1);
	i = -1;
	while (**cmd_str && !is_op_token(**cmd_str))
	{
		if (**cmd_str != ' ' && get_arg(cmd_str, dst->argv[++i], env))
			return (1);
		(*cmd_str) += (**cmd_str != '\0');
	}
}

int	main(int argc, char **argv, char **envp)
{
	
}
