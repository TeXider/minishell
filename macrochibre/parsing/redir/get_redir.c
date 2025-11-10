/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/11/10 11:10:04 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static void	set_cmd_fds(t_cmd *dst, int fd, t_rtype type)
// {
// 	dst->fd_in += (fd - dst->fd_in) * (type <= IN);
// 	dst->append_mode = (type == APPND || (dst->append_mode && type >= OUT));
// 	dst->fd_out += (fd - dst->fd_out) * (type >= OUT);
// 	dst->is_fd_in_pipe &= !(type <= IN);
// 	dst->is_fd_out_pipe &= !(type >= OUT);
// }

static void	add_char_to_name(t_cmd_parsing *cmdp, size_t *i)
{
	if (cmdp->sep != ' ' || *(cmdp->str) != ' ')
	{
		cmdp->cmd->redirv[cmdp->redirv_i].name[*i] = *(cmdp->str);
		(*i)++;
	}
	cmdp->str++;
}

static void	update_sep(t_cmd_parsing *cmdp, bool *has_quotes)
{
	set_sep(cmdp);
	*has_quotes = true;
	cmdp->str++;
}

static int	get_redir_name(t_cmd_parsing *cmdp, t_rtype type, t_env *env)
{
	size_t	len;
	size_t	i;
	bool	has_quotes;

	if (get_redir_name_len(cmdp->str, &len, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(&cmdp->cmd->redirv[cmdp->redirv_i].name, len, env))
		return (SYS_ERR);
	has_quotes = false;
	i = 0;
	while (!is_end_of_redir(cmdp))
	{
		if (change_of_sep(cmdp))
			update_sep(cmdp, &has_quotes);
		else if (type != HDOC && is_var(cmdp))
			expand(cmdp, env);
		else
			add_char_to_name(cmdp, &i);
		if (is_end_of_expand(cmdp))
			exit_expand(cmdp);
	}
	return (SUCCESS + HAS_QUOTES * has_quotes);
}

bool	get_redir(t_cmd_parsing *cmdp, t_env *env)
{
	int		status;
	t_rtype	type;

	cmdp->cmd->redirv[cmdp->redirv_i].name = NULL;
	type = HDOC * (*(cmdp->str) == '<' && *(cmdp->str + 1) == '<')
			+ APPND * (*(cmdp->str) == '>' && *(cmdp->str + 1) == '>');
	type += !type * (IN * (*(cmdp->str) == '<')
			+ OUT * (*(cmdp->str) == '>'));
	cmdp->str += 1 + (type == HDOC || type == APPND);
	skip_spaces(&cmdp->str);
	status = get_redir_name(cmdp, type, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
	{
		handle_redir_err(cmdp, status, env);
		return (true);
	}
	cmdp->cmd->redirv[cmdp->redirv_i].type = type;
	if (type == HDOC /*&& open_hdoc(cmdp, env)*/)
		return (true);
	cmdp->redirv_i++;
	return (false);
}

int	main(int argc, char **argv)
{
	(void) argc; (void) argv;
	t_env	env;
	//env.empty_list = empty_list;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller=    'c"; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=fra ka ka ";
	t_cmd_parsing cmdp;
	t_cmd cmd;
	t_redir	redir;
	redir.name = NULL;
	redir.type = 0;
	cmd.redirv = &redir;
	cmdp.cmd = &cmd;
	cmdp.argv_len = 0;
	cmdp.redirv_i = 0;
	cmdp.saved_str = NULL;
	cmdp.sep = ' ';
	cmdp.str = malloc(sizeof(char) * 257);
	cmdp.in_expand = false;
	ssize_t rd = read(1, cmdp.str, 256);
	if (rd == -1)
		return (1);
	cmdp.str[rd] = '\0';
	if (get_redir(&cmdp, &env))
		printf("Yo mama so fat she can't correctly parse a redir\n");
	else
		printf("redir: %s\ntype : %d\n", redir.name, redir.type);
}
