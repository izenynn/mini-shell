/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:11 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/23 13:59:41 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	ft_echo(char **str)
{
	int		i;

	i = 1;
	if (!str[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strncmp(str[1], "-n", 2) == 0)
	{
		i++;
		while (str[i][0] == '-' && str[i][1] == 'n')
			i++;
		while (str[i])
		{
			write(1, str[i], ft_strlen(str[i]));
			if (str[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else
	{
		i = 1;
		while (str[i])
		{
			write(1, str[i], ft_strlen(str[i]));
			if (str[i + 1])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
	return (0);
}
