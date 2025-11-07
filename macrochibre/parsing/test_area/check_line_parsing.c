/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:33:26 by almighty          #+#    #+#             */
/*   Updated: 2025/11/07 09:25:28 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	check_line_parsing(char *line, size_t *cmd_list_len, t_env *env)
{
	t_cmd_parsing	tmp_cmdp;
	bool			is_empty;
	bool			has_cmd;

	init_cmd_parsing(&tmp_cmdp, line);
	has_cmd = false;
	while (*(tmp_cmdp.str) && *(tmp_cmdp.str) != '\n')
	{
		is_empty = true;
		if (go_to_end_of_cmd(&tmp_cmdp, cmd_list_len, &is_empty, env))
			return (true);
		has_cmd |= !is_empty;
		if (has_cmd && is_empty)
		{
			create_error(tmp_cmdp.str, UNEXPECTED_TOKEN_ERR, env);
			return (true);
		}
		tmp_cmdp.str += (*(tmp_cmdp.str) == '|');
	}
	if (has_cmd && (is_empty || (*(tmp_cmdp.str - 1) == '|')))
	{
		create_error(tmp_cmdp.str, UNEXPECTED_TOKEN_ERR, env);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	(void) argc; (void) argv;
	char *empty_list[2];
	t_env	env;
	empty_list[0] = NULL; empty_list[1] = NULL;
	env.empty_list = empty_list;
	env.empty_string = "\0";
	env.envp = malloc(sizeof(char *) * 4);
	env.envp[3] = NULL;
	env.envp[0] = "bousiller=   c "; env.envp[1] = "kirikou=balletrou"; env.envp[2] = "fort=fra ka ka ";
	t_cmd_parsing cmdp;
	cmdp.argv_len = 0;
	cmdp.redirv_len = 0;
	cmdp.saved_str = NULL;
	cmdp.sep = ' ';
	cmdp.str = malloc(sizeof(char) * 257);
	ssize_t rd = read(1, cmdp.str, 256);
	if (rd == -1)
		return (1);
	cmdp.str[rd] = '\0';
	size_t	list_len = 0;
	if (check_line_parsing(cmdp.str, &list_len, &env))
		printf("Yo mama so fat she can't correctly parse a line\n");
	printf("list_len: %zu\n", list_len);
}