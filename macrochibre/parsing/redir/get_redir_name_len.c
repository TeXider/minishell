/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_name_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:50:26 by tpanou-d          #+#    #+#             */
/*   Updated: 2025/11/10 10:42:01 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	increment_len(t_cmd_parsing *cmdp, size_t *len, bool *end_of_redir,
	bool *has_arg)
{
	(*len) += (cmdp->sep != ' ' || *(cmdp->str) != ' ');
	*has_arg = (*len != 0);
	*end_of_redir |= (*has_arg && cmdp->sep == ' ' && *(cmdp->str) == ' ');
	cmdp->str++;
}

static void	update_sep(t_cmd_parsing *cmdp, bool *has_arg)
{
	set_sep(cmdp);
	*has_arg = true;
	cmdp->str++;
}

bool	get_redir_name_len(char *redir, size_t *len, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	bool			end_of_redir;
	bool			has_arg;

	*len = 0;
	end_of_redir = false;
	has_arg = false;
	init_cmd_parsing(&tmp_cmdp, redir);
	while (!is_end_of_redir(&tmp_cmdp))
	{
		if (end_of_redir && *(tmp_cmdp.str) != ' ')
			return (true);
		if (change_of_sep(&tmp_cmdp))
			update_sep(&tmp_cmdp, &has_arg);
		else if (is_var(&tmp_cmdp))
			expand(&tmp_cmdp, env);
		else
			increment_len(&tmp_cmdp, len, &end_of_redir, &has_arg);
		if (is_end_of_expand(&tmp_cmdp))
			exit_expand(&tmp_cmdp);
	}
	return (!*len);
}
