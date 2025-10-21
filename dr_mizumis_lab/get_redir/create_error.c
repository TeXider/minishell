/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 08:14:55 by almighty          #+#    #+#             */
/*   Updated: 2025/10/08 11:36:15 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_error(char *culprit, t_err ctxt, t_env *env)
{
	(void) culprit;
	(void) ctxt;
	(void) env;
	if (ctxt == SYS_ERR)
		perror("fark off mate");
	else if (ctxt == AMBI_REDIR_ERR)
		printf("ti as tue mon frere shang!\n");
	return (true);
}

bool	open_hdoc(char *delimiter, bool has_quotes, t_env *env)
{
	(void) env;
	printf("del : \"%s\", has_quotes : %d", delimiter, has_quotes);
	return (1234);
}