/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:11 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/24 18:58:08 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	put_str_no_nl(char *const *str, int i)
{
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
}

static void	put_strl_nl(char *const *str)
{
	int	i;

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
		put_str_no_nl(str, i);
	}
	else
		put_strl_nl(str);
	return (0);
}

