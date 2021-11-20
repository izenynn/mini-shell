/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 16:36:38 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

char	*ft_get_wdir(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char *) * PATH_MAX);
	if (getcwd(pwd, PATH_MAX))
		return (pwd);
	else
		return (NULL);
}
