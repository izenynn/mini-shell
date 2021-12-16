/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:26 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/16 21:34:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static int	validate_exit_code(char *const *exitc, int i)
{
	if (exitc && exitc[0] && exitc[1] && exitc[2])
	{
		if (g_sh.is_child == FALSE)
			write(STDERR_FILENO, "exit\n", 5);
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		return (1);
	}
	while (exitc[1] && exitc[1][i])
	{
		if (!ft_isdigit(exitc[1][i++]))
		{
			if (g_sh.is_child == FALSE)
				write(STDERR_FILENO, "exit\n", 5);
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 2;
			ft_lstclear(g_sh.env, free);
			free(g_sh.env);
			exit(2);
		}
	}
	return (0);
}

int	ft_exit(char **exitc)
{
	int	exit_code;
	int	i;

	i = 0;
	if (exitc[1] && (exitc[1][i] == '+' || exitc[1][i] == '-'))
		i++;
	if (validate_exit_code(exitc, i) == 1)
		return (1);
	if (exitc[1])
	{
		exit_code = ft_atoi(exitc[1]);
		g_sh.status = (unsigned char)exit_code;
		ft_lstclear(g_sh.env, free);
		free(g_sh.env);
		if (g_sh.is_child == FALSE)
			write(STDERR_FILENO, "exit\n", 5);
		exit((unsigned char)exit_code);
	}
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	if (g_sh.is_child == FALSE)
		write(STDERR_FILENO, "exit\n", 5);
	exit(g_sh.status);
	return (0);
}
