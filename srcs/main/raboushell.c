/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raboushell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:59:03 by almighty          #+#    #+#             */
/*   Updated: 2026/01/14 12:12:55 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/execution.h"

static inline void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->argv && *(cmd->argv) != cmd->path)
		safe_free((void **) &cmd->path);
	i = -1;
	while (cmd->argv && cmd->argv[++i])
		free(cmd->argv[i]);
	i = -1;
	while (++i < cmd->redirv_len)
	{
		safe_free((void **) &cmd->redirv[i].name);
		if (cmd->redirv[i].type == AMBI_REDIR)
			break ;
	}
	safe_free((void **) &cmd->redirv);
	safe_free((void **) &cmd->argv);
	safe_close(&cmd->fd_in, FD_NULL);
	safe_close(&cmd->fd_out, FD_NULL);
	free(cmd);
}

static inline void	free_shell_ops(t_shell_op *shell_op)
{
	t_shell_op	*next;

	while (shell_op)
	{
		if (shell_op->is_subshell)
			free_shell_ops(shell_op->op);
		else if (shell_op->op)
			free_cmd(shell_op->op);
		next = shell_op->next;
		free(shell_op);
		shell_op = next;
	}
}

// void	print_cmd_list(t_shell_op *cmd_list)
// {
// 	while (cmd_list)
// 	{
// 		if (cmd_list->is_subshell)
// 		{
// 			write(1, "[", 1);
// 			print_cmd_list((t_shell_op *) cmd_list->op);
// 			write(1, "]", 1);
// 		}
// 		else
// 		{
// 			t_cmd *cmd = cmd_list->op;
// 			write(1, "{", 1);
// 			for (int i = 0; cmd->argv[i]; i++)
// 			{
// 				print_str(cmd->argv[i]);
// 				write(1, ", ", 2);
// 			}
// 			write(1, "} ", 2);
// 		}
// 		if (cmd_list->op_type == PIPE_OP)
// 			write(1, "P", 1);
// 		else if (cmd_list->op_type == AND_OP)
// 			write(1, "AN", 2);
// 		else if (cmd_list->op_type == OR_OP)
// 			write(1, "OR", 2);
// 		else if (cmd_list->op_type == EMPTY_OP)
// 			write(1, "EM", 2);
// 		write(1, " ", 1);
// 		cmd_list = cmd_list->next;
// 	}
// }

void	raboushell(t_env *env)
{
	char		*prompt;
	char		*input;
	t_shell_op	*shell_op;

	shell_op = NULL;
	if (!get_prompt(&prompt, env)
		&& !get_line(&input, prompt, &env->get_line_env)
		&& !get_shell_line(input, &shell_op, env))
		exec_shell_op_line(shell_op, env);
	if (env->err)
		throw_error(env);
	free_shell_ops(shell_op);
	safe_free((void **) &prompt);
	safe_free((void **) &input);
}
