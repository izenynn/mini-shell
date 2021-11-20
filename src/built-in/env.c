/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:18 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 19:30:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	ft_env(const char *n)
{
	t_list	*head;

	head = g_sh.env;
	if (!g_sh.env)
		return ;
	if (!n)
	{
		while (g_sh.env)
		{
			write(1, g_sh.env->data, ft_strlen((char *) g_sh.env->data));
			write(1, "\n", 1);
			g_sh.env = g_sh.env->next;
		}
		g_sh.env = head;
		g_sh.status = 0;
	}
	else
	{
		write(1, "env: ", 5);
		write(1, n, ft_strlen(n));
		write(1, ": No such file or directory\n", 28);
	}
}
