/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:18 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 16:36:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	ft_env(void)
{
	t_list	*head;

	head = g_sh.env;
	if (!g_sh.env)
		return ;
	while (g_sh.env)
	{
		printf("%s\n", (char *) g_sh.env->data);
		g_sh.env = g_sh.env->next;
	}
	g_sh.env = head;
}
