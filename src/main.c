/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 18:37:34 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* global var */
t_sh	g_sh;

/* main */
int	main(int argc, char *argv[])
{
	char	*line;

	init_shell();
	handle_flags(argc, argv);
	while (1)
	{
		sig_parent();
		line = read_prompt();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(g_sh.status);
		}
		if (ft_strlen(line) <= 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		handle_line(line, TRUE);
	}
	return (EXIT_SUCCESS);
}
