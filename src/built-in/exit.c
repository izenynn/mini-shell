/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:26 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 19:46:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	ft_exit(char *exitc)
{
	int	exit_code;
	int	i;

	i = 0;
	while (exitc[i++])
	{
		if (ft_isdigit(exitc[i]) == 0)
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc, ft_strlen(exitc));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 1;
			exit(255);
		}
	}
	exit_code = ft_atoi(exitc);
	if (exit_code == -999)
		exit(0);
	g_sh.status = exit_code;
	exit(exit_code);
}
