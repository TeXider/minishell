/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 10:02:10 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 14:50:46 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	set_cmd_fds(t_cmd *dst, int fd, t_rtype type)
{
	dst->fd_in += (fd - dst->fd_in) * (type <= IN);
	dst->append_mode = (type == APPND || (dst->append_mode && type >= OUT));
	dst->fd_out += (fd - dst->fd_out) * (type >= OUT);
	dst->is_fd_in_pipe &= !(type <= IN);
	dst->is_fd_out_pipe &= !(type >= OUT);
}

static inline int	get_redir_name(t_cmd_parsing *cmdp, t_env *env)
{
	size_t	len;
	size_t	i;

	if (get_redir_name_len(cmdp->str, &len, env))
		return (AMBI_REDIR_ERR);
	if (safe_challoc(&cmdp->cmd->redirv[i].name, len, env))
		return (SYS_ERR);
	i = 0;
	while (!is_end_of_arg(cmdp))
	{
		if (change_of_sep(cmdp))
			set_sep(cmdp);
		else if (is_var(*redir, grn.sep))
			redir_expand(redir, *name, &grn, env);
		else
			(*name)[grn.i++] = **redir;
		(*redir)++;
	}
	return (SUCCESS + HAS_QUOTES);
}

bool	get_redir(t_cmd_parsing *cmdp, t_env *env)
{
	int		status;
	t_rtype	type;
	int		fd;

	cmdp->cmd->redirv[cmdp->redirv_i].name = NULL;
	type = 
	type += !type * (IN * (*(cmdp->str) == '<')
		+ OUT * (*(cmdp->str) == '>') - type)
		+ APPND * (*(cmdp->str) == '>' && *(cmdp->str + 1) == '>');
	cmdp->str += (type == APPND);
	skip_spaces(&cmdp->str);
	status = get_redir_name(cmdp, env);
	if (status == AMBI_REDIR_ERR || status == SYS_ERR)
	{
		handle_redir_err(*redir, status, env);
		return (true);
	}
	fd = open_redir(cmdp, (status == HAS_QUOTES), env);
	if (fd == -1)
		return (true);
	close_prev_redir(cmdp);
	set_cmd_fds(dst, type, fd);
	return (false);
}

//int	main(int argc, char **argv)
//{
//	(void) argc; (void) argv;
//	char *empty_list[2];
//	t_env	env;
//	empty_list[0] = NULL; empty_list[1] = NULL;
//	env.empty_list = empty_list;
//	env.empty_string = "\0";
//	env.envp = malloc(sizeof(char *) * 4);
//	env.envp[3] = NULL;
//	env.envp[0] = "bousiller=    c"; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=fra ka ka ";
//	t_cmd_parsing cmdp;
//	cmdp.argv_len = 0;
//	cmdp.saved_str = NULL;
//	cmdp.sep = ' ';
//	cmdp.str = malloc(sizeof(char) * 257);
//	ssize_t rd = read(1, cmdp.str, 256);
//	if (rd == -1)
//		return (1);
//	cmdp.str[rd] = '\0';
//	size_t	list_len = 0;
//	if (get_redir_name_len(cmdp.str, &list_len, &env))
//		printf("Yo mama so fat she can't correctly parse a line\n");
//	printf("list_len: %zu\n", list_len);
//}
