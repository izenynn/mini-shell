/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:11 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/21 13:08:09 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	ft_echo(const char *str, const char *flag)
{
	if (!str)
		write(1, "\n", 1);
	else if (ft_strncmp(flag, "-n", 3) == 0)
	{
		g_sh.status = 0;
		write(1, str, ft_strlen(str));
	}
	else
	{
		g_sh.status = 0;
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	return (0);
}
