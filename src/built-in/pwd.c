/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/27 08:50:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	print_pwd(const char *pwd)
{
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
}

void error_handler(char *pwd) {
	write(1, "pwd: too many arguments\n", 24);
	free(pwd);
}

int	ft_get_wdir(char **n)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (1);
	if (n[1])
	{
		error_handler(pwd);
		return (1);
	}
	else
	{
		if (getcwd(pwd, PATH_MAX) == NULL)
		{
			free(pwd);
			pwd = NULL;
		}
		if (pwd == NULL)
			pwd = ft_getenv("PWD");
		if (pwd == NULL)
			return (1);
		print_pwd(pwd);
		free(pwd);
	}
	return (0);
}
