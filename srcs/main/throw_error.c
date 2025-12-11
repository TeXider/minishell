/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:24:58 by almighty          #+#    #+#             */
/*   Updated: 2025/12/11 18:57:38 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"
#include "string.h"

static inline void	add_culprit_err_msg(char *err_msg, size_t *len, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < CULPRIT_LENGTH && env->culprit[i])
	{
		err_msg[*len] = env->culprit[i];
		(*len)++;
		i++;
	}
	if (i == CULPRIT_LENGTH && env->culprit[i])
	{
		err_msg[*len - 1] = '.';
		err_msg[*len - 2] = '.';
		err_msg[*len - 3] = '.';
	}
	if (env->err != UNCLOSED_QUOTES_ERR && env->err != UNEXPECTED_TOKEN_ERR)
	{
		err_msg[*len] = ':';
		err_msg[*len + 1] = ' ';
		*len += 2;
	}
}

static inline void	write_err_msg(char *err_msg, size_t *len, char *msg,
	t_env *env)
{
	if (env->err != UNCLOSED_QUOTES_ERR && env->err != UNEXPECTED_TOKEN_ERR)
		add_culprit_err_msg(err_msg, len, env);
	while (*msg)
	{
		err_msg[*len] = *msg;
		(*len)++;
		msg++;
	}
	if (env->err == UNCLOSED_QUOTES_ERR || env->err == UNEXPECTED_TOKEN_ERR)
		add_culprit_err_msg(err_msg, len, env);
	err_msg[*len] = '\n';
	(*len)++;
}

static inline void	set_err_msg(char *err_msg, size_t *len, t_env *env)
{
	char	*msg;

	msg = NULL;
	if (env->err == UNCLOSED_QUOTES_ERR)
		msg = "unclosed quote ";
	else if (env->err == UNEXPECTED_TOKEN_ERR)
		msg = "unexpected token ";
	else if (env->err == AMBI_REDIR_ERR)
		msg = "ambiguous redirection";
	else if (env->err == CMD_NOT_FOUND_ERR)
		msg = "command not found";
	else if (env->err == CMD_FILE_NOT_FOUND_ERR)
		msg = "No such file or directory";
	else if (env->err == CMD_NOT_EXEC_ERR)
		msg = "Permission denied";
	else if (env->err == CMD_IS_DIR_ERR)
		msg = "Is a directory";
	else if ((env->err == FILE_ERR || env->err == SYS_ERR
		|| env->err == TERM_ERR || env->err == FATAL_SYS_ERR))
		msg = strerror(errno);
	write_err_msg(err_msg, len, msg, env);
}

static inline void	set_err_ctxt(char *err_msg, size_t *len, t_env *env)
{
	char	*ctxt;

	ctxt = NULL;
	if (env->err == UNCLOSED_QUOTES_ERR || env->err == UNEXPECTED_TOKEN_ERR)
		ctxt = ETXT"PARSING ERROR:"RST" ";
	else if (env->err == FILE_ERR)
		ctxt = ETXT"FILE ERROR:"RST" ";
	else if (env->err == AMBI_REDIR_ERR)
		ctxt = ETXT"REDIRECT ERROR:"RST" ";
	else if (env->err == CMD_NOT_FOUND_ERR
		|| env->err == CMD_FILE_NOT_FOUND_ERR
		|| env->err == CMD_NOT_EXEC_ERR
		|| env->err == CMD_IS_DIR_ERR)
		ctxt = ETXT"EXECUTION ERROR:"RST" ";
	else if (env->err == SYS_ERR)
		ctxt = ETXT"SYSTEM ERROR:"RST" ";
	else if (env->err == TERM_ERR)
		ctxt = ETXT"TERMINAL ERROR:"RST" ";
	else if (env->err == FATAL_SYS_ERR)
		ctxt = ETXT"FATAL SYSTEM ERROR:"RST" ";
	while (ctxt[*len])
	{
		err_msg[*len] = ctxt[*len];
		(*len)++;
	}
}

void	throw_error(t_env *env)
{
	char	err_msg[CULPRIT_LENGTH + 105];
	size_t	err_msg_len;

	if (env->err != BUILTIN_ERR)
	{
		err_msg_len = 0;
		set_err_ctxt(err_msg, &err_msg_len, env);
		set_err_msg(err_msg, &err_msg_len, env);
		print_raboushell();
		write(2, err_msg, err_msg_len);
		// if (env->err == FILE_ERR || env->err == SYS_ERR || env->err == TERM_ERR
		// 	|| env->err == FATAL_SYS_ERR)
		// 	perror(NULL);
	}
	env->err = SUCCESS;
	write(2, RST, 4);
}
