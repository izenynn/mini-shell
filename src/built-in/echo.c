/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:11 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 16:36:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	ft_echo(const char *str, const char *flag)
{
	if (!str)
		return (1);
	if (ft_strncmp(flag, "-n", 3) == 0)
	{
		printf("%s", str);
		return (0);
	}
	else
	{
		printf("%s\n", str);
		return (0);
	}
}
