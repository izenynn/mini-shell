/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/02 16:59:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	print_pwd(const char *pwd)
{
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
}

int	ft_get_wdir(char **n)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (1);
	(void)n;
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
	return (0);
}
