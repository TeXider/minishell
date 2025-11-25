/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpt2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almighty <almighty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:22:54 by almighty          #+#    #+#             */
/*   Updated: 2025/11/24 14:27:47 by almighty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"
int main()
{
	char buff[256];
	int a = fork();
	if (!a)
	{
		read(0, buff, 1);
		exit(0);
	}
	wait(NULL);
	a = fork();
	if (!a)
	{
		read(0, buff, 1);
		exit(0);
	}
	wait(NULL);
	read(0, buff, 1);
	write(1, buff, 1);
	write(1, "\n", 1);
}