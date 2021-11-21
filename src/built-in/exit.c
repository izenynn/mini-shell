/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:26 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/21 14:39:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_nbr.h"
#include <sh.h>

void	ft_exit(char *exitc)
{
	int	exit_code;
	int i;

	i = 0;
	if (exitc[i] == '+' || exitc[i] == '-')
		i++;
	while (exitc[i])
	{
		if (!ft_isdigit(exitc[i++]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc, ft_strlen(exitc));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 1;
			exit(2);
		}
	}	
	exit_code = ft_atoi(exitc);
	exit((unsigned char)exit_code);
	g_sh.status = exit_code;
	exit(exit_code);
}
