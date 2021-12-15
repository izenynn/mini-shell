/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:26 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/15 20:00:37 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_nbr.h>
#include <sh.h>

static void	validate_exit_code(char *const *exitc, int i)
{
	while (exitc[1] && exitc[1][i])
	{
		if (!ft_isdigit(exitc[1][i++]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 2;
			ft_lstclear(g_sh.env, free);
			free(g_sh.env);
			exit(2);
		}
	}
}

int	ft_exit(char **exitc)
{
	int	exit_code;
	int	i;

	i = 0;
	if (exitc && exitc[0] && exitc[1] && exitc[2])
	{
		write(STDOUT_FILENO, "exit\nexit: too many arguments\n", 30);
		return (1);
	}
	if (exitc[1] && (exitc[1][i] == '+' || exitc[1][i] == '-'))
		i++;
	validate_exit_code(exitc, i);
	if (exitc[1])
	{
		exit_code = ft_atoi(exitc[1]);
		g_sh.status = (unsigned char)exit_code;
		ft_lstclear(g_sh.env, free);
		free(g_sh.env);
		write(STDOUT_FILENO, "exit\n", 5);
		exit((unsigned char)exit_code);
	}
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	g_sh.status = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	exit(0);
	return (0);
}
