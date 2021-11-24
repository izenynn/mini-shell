/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:26 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/22 19:20:25 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_nbr.h"
#include <sh.h>

int	ft_exit(char **exitc)
{
	int	exit_code;
	int	i;

	i = 0;
	if (exitc[1] && (exitc[1][i] == '+' || exitc[1][i] == '-'))
		i++;
	while (exitc[1] && exitc[1][i])
	{
		if (!ft_isdigit(exitc[1][i++]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 1;
			exit(2);
		}
	}
	if (exitc[1])
	{	
		exit_code = ft_atoi(exitc[1]);
		exit((unsigned char)exit_code);
		g_sh.status = exit_code;
		exit(exit_code);
	}
	ft_lstclear(&g_sh.env, free);
	exit(0);
	return (0);
}
