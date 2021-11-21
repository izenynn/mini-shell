/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:32:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 13:32:37 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

char	*ft_getenv(const char *path)
{
	int		path_size;
	char	*ret;
	t_list	*head;

	head = g_sh.env;
	path_size = ft_strlen(path);
	while (g_sh.env)
	{
		if (ft_strncmp(path, (char *)g_sh.env->data, path_size) == 0)
		{
			ret = ft_substr((char *)g_sh.env->data, path_size + 1,
					ft_strlen((char *)g_sh.env->data) - path_size);
			g_sh.env = head;
			return (ret);
		}
		g_sh.env = g_sh.env->next;
	}
	return (NULL);
}
