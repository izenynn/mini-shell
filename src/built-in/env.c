/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:18 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/30 19:14:02 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	printer(void)
{
	int		i;
	int		cnt;
	char	*data;
	t_list	*aux;

	aux = g_sh.env;
	while (aux)
	{
		i = 0;
		cnt = 1;
		data = (char *)aux->data;
		while (data[i] && data[i] != '=')
			i++;
		if (data[i] == '=')
		{
			write(1, aux->data, ft_strlen((char *)aux->data));
			write(1, "\n", 1);
		}
		aux = aux->next;
	}
}

int	ft_env(char **n)
{
	if (!g_sh.env)
		return (0);
	if (n[1] == NULL)
	{
		printer();
	}
	else
	{
		write(STDERR_FILENO, "env: ", 5);
		write(STDERR_FILENO, n[1], ft_strlen(n[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (127);
	}
	return (0);
}
