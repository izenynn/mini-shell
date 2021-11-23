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

int	ft_echo(const char **str)
{
	/*char	*nstr;
	int		i;

	i = 0;
	if (!str)
		write(1, "\n", 1);
	else if (ft_strncmp(str[1], "-n", 3) == 0)
	{
		if (str[1][0] == '-' && str[1][1] == 'n')
		{
			while (str[i][0] == '-' && str[i][1] == 'n')
				i++;
		}
		nstr = ft_substr(str[i]);
		g_sh.status = 0;
		write(1, nstr, ft_strlen(nstr));
		free(nstr);
	}
	else
	{
		g_sh.status = 0;
		write(1, str[1], ft_strlen(str[1]));
		write(1, "\n", 1);
	}*/
	(void)str;
	write(STDOUT_FILENO, "you execute the echo command :D\n", 32);
	return (0);
}
