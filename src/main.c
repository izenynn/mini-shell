/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 21:34:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* global var */
t_sh	g_sh;

/* main */
int	main(void)
{
	char	*line;

	init_shell();
	while (1)
	{
		sig_parent();
		line = read_prompt();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit (g_sh.status);
		}
		if (ft_strlen(line) <= 0)
			continue ;
		add_history(line);
		handle_line(line);
	}
	return (EXIT_SUCCESS);
}
