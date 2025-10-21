/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:14:55 by almighty          #+#    #+#             */
/*   Updated: 2025/10/17 09:22:12 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(t_env *env)
{
	if (env->err == SYS_ERR || env->err == CLOSE_ERR || env->err == FILE_ERR)
		{printf("%s ", env->culprit); perror("wallah c'est le systeme pas moi");}
	else if (env->err == AMBI_REDIR_ERR)
		printf("tu pouvais pas etre plus clair dans tes redirections\n");
	else if (env->err == UNCLOSED_QUOTES_ERR)
		printf("t'as pas fermé la quote zeubi : %c\n", *(env->culprit));
	else if (env->err == UNEXPECTED_TOKEN_ERR)
		printf("balletrou qu'est-ce que tu veux que je fasse avec ça: %c\n", *(env->culprit));	
	exit(0);
}

bool	create_error(char *culprit, t_err err, t_env *env)
{
	size_t	i;
	
	env->err = err;
	i = -1;
	while (culprit[++i])
	{
		env->culprit[i] = culprit[i];
	}
	return (true);
}

int	open_hdoc(char *delimiter, bool has_quotes, t_env *env)
{
	(void) env;
	printf("del : \"%s\", has_quotes : %d", delimiter, has_quotes);
	return (-2);
}