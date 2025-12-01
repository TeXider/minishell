/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:06:32 by almighty          #+#    #+#             */
/*   Updated: 2025/12/01 11:58:32 by tpanou-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static inline bool	atouc(char *num_str, t_uchar *res)
{
	bool	is_neg;
	long	res_tmp;
	size_t	i;

	while (*num_str && *num_str == ' ')
		num_str++;
	is_neg = (*num_str == '-');
	num_str += is_neg || (*num_str == '+');
	res_tmp = 0;
	i = 0;
	while (i < 19 && num_str[i] && num_str[i] >= '0' && num_str[i] <= '9')
	{
		if ((is_neg && res_tmp == 922337203685477580 && num_str[i] > '8')
			|| (!is_neg && res_tmp == 922337203685477580 && num_str[i] > '7')
			|| (res_tmp > 922337203685477580))
			return (true);
		res_tmp = num_str[i] - '0' + res_tmp * 10;
		i++;
	}
	while (num_str[i] && num_str[i] == ' ')
		i++;
	res_tmp *= 1 - 2 * is_neg;
	*res = (t_uchar) res_tmp;
	return (i == 0 || num_str[i]);
}

bool	builtin_exit(char **args, t_env *env)
{
	if (!*args)
		return (false);
	if (atouc(*args, &env->exit_code))
	{
		throw_builtin_error(*args, EXIT_ERR, NUM_ARG_BERR, env);
		return (true);
	}
	if (*(args + 1))
	{
		throw_builtin_error(NULL, EXIT_ERR, TOO_MANY_PARAMS_BERR, env);
		return (true);
	}
	set_exit_code(env->exit_code, env);
	env->end_of_raboushell = true;
	return (false);
}
