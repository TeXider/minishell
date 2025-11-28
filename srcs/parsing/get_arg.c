/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:44:15 by almighty          #+#    #+#             */
/*   Updated: 2025/11/14 14:23:55 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_char_to_arg(t_cmd_parsing *cmdp, size_t *arg_i)
{
	if (cmdp->sep != ' ' || *(cmdp->str) != ' ')
	{
		cmdp->curr_arg[*arg_i] = *(cmdp->str);
		(*arg_i)++;
	}
	cmdp->cmd->cmd_name_is_path |= (!cmdp->argv_i && *(cmdp->str) == '/');
	cmdp->str++;
}

static void	update_sep(t_cmd_parsing *cmdp, bool *has_arg)
{
	set_sep(cmdp);
	if (has_arg)
		*has_arg = true;
	cmdp->str++;
}

static bool	get_arg_len(char *str, size_t *len, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	bool			has_arg;

	*len = 0;
	has_arg = false;
	init_cmd_parsing(&tmp_cmdp, str);
	while ((!has_arg && tmp_cmdp.in_expand) || !is_end_of_arg(&tmp_cmdp))
	{
		if (change_of_sep(&tmp_cmdp))
			update_sep(&tmp_cmdp, &has_arg);
		else if (is_var(&tmp_cmdp))
			expand(&tmp_cmdp, env);
		else
		{
			(*len) += (tmp_cmdp.sep != ' ' || *(tmp_cmdp.str) != ' ');
			has_arg = (*len != 0);
			tmp_cmdp.str++;
		}
		if (is_end_of_expand(&tmp_cmdp))
			exit_expand(&tmp_cmdp);
	}
	return (!has_arg);
}

bool	get_arg(t_cmd_parsing *cmdp, t_env *env)
{
	size_t	len;
	size_t	arg_i;

	if (get_arg_len(cmdp->str, &len, env))
	{
		go_to_end_of_arg(cmdp, env);
		return (false);
	}
	if (safe_challoc(cmdp->cmd->argv + cmdp->argv_i, len, env))
		return (true);
	cmdp->curr_arg = cmdp->cmd->argv[cmdp->argv_i];
	arg_i = 0;
	while ((!arg_i && cmdp->in_expand) || !is_end_of_arg(cmdp))
	{
		if (change_of_sep(cmdp))
			update_sep(cmdp, NULL);
		else if (is_var(cmdp))
			expand(cmdp, env);
		else
			add_char_to_arg(cmdp, &arg_i);
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	cmdp->argv_i++;
	return (false);
}
