/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:24:58 by almighty          #+#    #+#             */
/*   Updated: 2025/12/02 12:55:06 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void add_culprit_err_msg(char *err_msg, size_t *len, t_env *env)
{
	size_t	i;

	if (env->err == UNCLOSED_QUOTES_ERR || env->err == UNEXPECTED_TOKEN_ERR)
	{
		err_msg[*len] = '`';
		err_msg[*len + 1] = *(env->culprit);
		err_msg[*len + 2] = '\'';
		err_msg[*len + 3] = '\n';
		*len += 4;
	}
	else
	{
		i = -1;
		while (env->culprit[++i])
		{
			err_msg[*len] = env->culprit[i];
			(*len)++;
		}
		err_msg[*len] = ':';
		err_msg[*len + 1] = ' ';
		*len += 2;
	}
}

static inline void set_err_culprit(char *err_msg, size_t *len, char *msg,
	t_env *env)
{
	if (env->err != UNCLOSED_QUOTES_ERR && env->err != UNEXPECTED_TOKEN_ERR)
		add_culprit_err_msg(err_msg, len, env);
	if (env->err != SYS_ERR && env->err != TERM_ERR)
	{	
		while (*msg)
		{
			err_msg[*len] = *msg;
			(*len)++;
			msg++;
		}
	}
	if (env->err == UNCLOSED_QUOTES_ERR || env->err == UNEXPECTED_TOKEN_ERR)
		add_culprit_err_msg(err_msg, len, env);
}

static inline void set_err_msg(char *err_msg, size_t *len, t_env *env)
{
	char	*msg;

	if (env->err == UNCLOSED_QUOTES_ERR)
		msg = "unclosed quote ";
	else if (env->err == UNEXPECTED_TOKEN_ERR)
		msg = "unexpected token ";
	else if (env->err == AMBI_REDIR_ERR)
		msg = "ambiguous redirection\n";
	else if (env->err == CMD_NOT_FOUND_ERR)
		msg = "command not found\n";
	else if (env->err == CMD_FILE_NOT_FOUND_ERR)
		msg = "No such file or directory\n";
	else if (env->err == CMD_NOT_EXEC_ERR)
		msg = "Permission denied\n";
	else if (env->err == CMD_IS_DIR_ERR)
		msg = "Is a directory\n";
	set_err_culprit(err_msg, len, msg, env);
}

static inline void set_err_ctxt(char *err_msg, size_t *len, t_env *env)
{
	char	*ctxt;
	
	if (env->err == UNCLOSED_QUOTES_ERR || env->err == UNEXPECTED_TOKEN_ERR)
		ctxt = ETXT"PARSING ERROR:"RST" ";
	else if (env->err == FILE_ERR || env->err == AMBI_REDIR_ERR)
		ctxt = ETXT"FILE ERROR:"RST" ";
	else if (env->err == CMD_NOT_FOUND_ERR
		|| env->err == CMD_FILE_NOT_FOUND_ERR
		|| env->err == CMD_NOT_EXEC_ERR)
		ctxt = ETXT"EXECUTION ERROR:"RST" ";
	else if (env->err == TERM_ERR)
		ctxt = ETXT"TERMINAL ERROR:"RST" ";
	else if (env->err == SYS_ERR)
		ctxt = ETXT"SYSTEM ERROR:"RST" ";
	while (ctxt[*len])
	{
		err_msg[*len] = ctxt[*len];
		(*len)++;
	}
}

void	throw_error(t_env *env)
{
	char	err_msg[CULPRIT_LENGTH + 100];
	size_t	err_msg_len;

	if (env->err)
	{
		if (env->err != BUILTIN_ERR)
		{
			err_msg_len = 0;
			set_err_ctxt(err_msg, &err_msg_len, env);
			set_err_msg(err_msg, &err_msg_len, env);
			print_raboushell();
			write(2, err_msg, err_msg_len);
			if (env->err == SYS_ERR || env->err == TERM_ERR)
				perror(NULL);
		}
		env->err = SUCCESS;
		write(2, RST, 4);
	}
}
