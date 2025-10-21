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

bool	create_error(char *culprit, t_err err, t_env *env)
{
	(void) culprit;
	(void) err;
	(void) env;
	if (err == SYS_ERR || err == CLOSE_ERR || err == FILE_ERR)
		perror("wallah c'est le systeme pas moi");
	else if (err == AMBI_REDIR_ERR)
		printf("tu pouvais pas etre plus clair dans tes redirections\n");
	else if (err == UNCLOSED_QUOTES_ERR)
		printf("t'as pas fermé la quote zeubi : %c\n", *culprit);
	else if (err == UNEXPECTED_TOKEN_ERR)
		printf("balletrou qu'est-ce que tu veux que je fasse avec ça: %c\n", *culprit);
	return (true);
}
