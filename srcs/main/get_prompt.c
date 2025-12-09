/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:53:31 by almighty          #+#    #+#             */
/*   Updated: 2025/12/09 12:10:24 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raboushell.h"

static inline void	write_on_prompt(char *str, char *prompt, size_t *prompt_i)
{
	while (*str)
	{
		prompt[*prompt_i] = *str;
		str++;
		(*prompt_i)++;
	}
}

static inline size_t	prompt_len(char *user_var, char *pwd_var)
{
	size_t	usr_len;
	size_t	pwd_len;

	usr_len = 0;
	pwd_len = 0;
	while (user_var[usr_len]
		|| pwd_var[pwd_len])
	{
		usr_len += (user_var[usr_len] != '\0');
		pwd_len += (pwd_var[pwd_len] != '\0');
	}
	return (usr_len + pwd_len + 37);
}

static inline char	*find_pwd_var(char **envp)
{
	while (*envp)
	{
		if (*(*envp) == 'P'
			&& *(*envp + 1) == 'W'
			&& *(*envp + 2) == 'D'
			&& *(*envp + 3) == '=')
			return (*envp + 4);
		envp++;
	}
	return ("\0");
}

static inline char	*find_user_var(char **envp)
{
	while (*envp)
	{
		if (*(*envp) == 'U'
			&& *(*envp + 1) == 'S'
			&& *(*envp + 2) == 'E'
			&& *(*envp + 3) == 'R'
			&& *(*envp + 4) == '=')
			return (*envp + 5);
		envp++;
	}
	return ("\0");
}

bool	get_prompt(char **dst, t_env *env)
{
	char	*user_var;
	char	*pwd_var;
	size_t	i;

	user_var = find_user_var(env->envp);
	pwd_var = find_pwd_var(env->envp);
	if (safe_challoc(dst, prompt_len(user_var, pwd_var), env))
		return (true);
	i = 0;
	write_on_prompt(BOLD "["SGREEN, *dst, &i);
	write_on_prompt(user_var, *dst, &i);
	write_on_prompt(" "RST BCYAN, *dst, &i);
	write_on_prompt(pwd_var, *dst, &i);
	write_on_prompt(RST BOLD"]$ "RST, *dst, &i);
	return (false);
}