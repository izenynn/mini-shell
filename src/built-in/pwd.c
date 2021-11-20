/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 17:21:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	ft_get_wdir(void)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (1);
	if (getcwd(pwd, PATH_MAX))
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		free(pwd);
		return (0);
	}
	else
	{
		free(pwd)
		return (1);
	}
}
