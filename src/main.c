/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/30 13:26:59 by dpoveda-         ###   ########.fr       */
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
			exit (EXIT_SUCCESS);
		}
		if (ft_strlen(line) <= 0)
			continue ;
		add_history(line);
		handle_line(line);
	}
	return (EXIT_SUCCESS);
}
