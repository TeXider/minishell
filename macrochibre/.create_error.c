/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:14:55 by almighty          #+#    #+#             */
/*   Updated: 2025/11/18 17:42:57 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_error(t_env *env)
{
	if (env->err == SYS_ERR || env->err == FILE_ERR)
		{printf("%s ", env->culprit); perror("wallah c'est le systeme pas moi");}
	else if (env->err == AMBI_REDIR_ERR)
		printf("tu pouvais pas etre plus clair dans tes redirections: %s\n", env->culprit);
	else if (env->err == UNCLOSED_QUOTES_ERR)
		printf("t'as pas fermé la quote zeubi : %c\n", *(env->culprit));
	else if (env->err == UNEXPECTED_TOKEN_ERR)
		printf("balletrou qu'est-ce que tu veux que je fasse avec ça: %c\n", *(env->culprit));
	else if (env->err == EXEC_ERR)
		printf("hocus pocus brocus focus nikkus niggus : %s\n", env->culprit);
	exit(env->err);
}

bool	create_error(char *culprit, t_err err, t_env *env)
{
	size_t	i;
	
	env->err = err;
	i = -1;
	while (++i < CULPRIT_LENGTH && culprit[i])
		env->culprit[i] = culprit[i];
	if (culprit[i] && i == CULPRIT_LENGTH)
	{
		env->culprit[i - 1] = '.';
		env->culprit[i - 2] = '.';
		env->culprit[i - 3] = '.';
	}
	env->culprit[i] = '\0';
	return (true);
}
