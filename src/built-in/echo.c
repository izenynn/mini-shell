/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:11 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/08 17:06:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	put_str_no_nl(char *const *str, int i)
{
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(STDOUT_FILENO, " ", 1);
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
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str && ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	ft_echo(char **str)
{
	int		i;

	i = 1;
	if (!str[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (check_flag(str[1]) == 0)
	{
		i++;
		while (str[i] && check_flag(str[i]) == 0)
			i++;
		if (!str[i])
			return (0);
		put_str_no_nl(str, i);
	}
	else
		put_strl_nl(str);
	return (0);
}
